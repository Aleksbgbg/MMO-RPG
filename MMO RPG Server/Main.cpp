#include <SFML/Network.hpp>

#include <iostream>

#include <MessageType.h>
#include <ServerInfo.h>

static void Unblock(sf::Socket& socket)
{
	socket.setBlocking(false);
}

static void Log(const sf::TcpSocket& playerSocket, const std::string& message)
{
	std::cout << "[" << playerSocket.getRemoteAddress() << ":" << playerSocket.getRemotePort() << "] " << message << ".\n";
}

int main()
{
	sf::TcpListener tcpListener{ };

	Unblock(tcpListener);

	if (tcpListener.listen(ServerPort) != sf::Socket::Done)
	{
		const std::string diagnostic = "TcpListener listening error.";

		std::cout << diagnostic << std::endl;

		throw std::runtime_error{ diagnostic };
	}

	std::cout << "Listening at " << ServerIp << " on port " << ServerPort << ".\n";

	sf::TcpSocket player{ };
	Unblock(player);

	bool connected = false;

	sf::Clock heartbeatTimer{ };

	while (true)
	{
		if (connected)
		{
			sf::Packet message{ };

			while (player.receive(message) == sf::Socket::Done)
			{
				int messageType;

				message >> messageType;

				switch (static_cast<MessageType>(messageType))
				{
				case MessageType::HeartbeatAck:
					heartbeatTimer.restart();

					Log(player, "Heartbeated");

					break;
				}
			}

			if (heartbeatTimer.getElapsedTime().asMilliseconds() > HeartbeatThresholdMs)
			{
				player.disconnect();

				connected = false;
				Log(player, "Disconnected");
			}
		}
		else
		{
			if (tcpListener.accept(player) == sf::Socket::Done)
			{
				connected = true;
				Log(player, "Connected");

				heartbeatTimer.restart();
			}
			
			sf::sleep(sf::milliseconds(1));
		}
	}

	return 0;
}