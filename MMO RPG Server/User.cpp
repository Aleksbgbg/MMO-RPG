#include "User.h"

#include <DataTransfer.h>
#include <MessageType.h>
#include <ServerInfo.h>

#include "Logger.h"

User::User(std::unique_ptr<sf::TcpSocket> userSocket)
	:
	socket{ std::move(userSocket) },
	connected{ true }
{
	socket->setBlocking(false);

	Log(*socket, "Connected");

	// Handshake
	{
		sf::Packet helloPacket;

		helloPacket << static_cast<int>(MessageType::Hello) << HeartbeatThresholdMs;

		sf::Socket::Status handshakeStatus;

		do
		{
			handshakeStatus = Send(*socket, helloPacket);
		} while (handshakeStatus == sf::Socket::NotReady);

		if (handshakeStatus != sf::Socket::Done)
		{
			Log(*socket, "Unable to establish handshake");
			Disconnect();
		}
	}

	heartbeatTimer.restart();
}

void User::Update()
{
	bool receiving = true;

	while (receiving)
	{
		receiving = false;

		sf::Packet message{ };

		switch (Receive(*socket, message))
		{
		case sf::Socket::Done:
		{
			int messageType;

			message >> messageType;

			switch (static_cast<MessageType>(messageType))
			{
			case MessageType::Heartbeat:
			{
				Log(*socket, "Heartbeated (" + std::to_string(heartbeatTimer.getElapsedTime().asMilliseconds()) + "ms)");
				heartbeatTimer.restart();

				sf::Packet heartbeatAck{ };

				heartbeatAck << static_cast<int>(MessageType::HeartbeatAck);

				Send(*socket, heartbeatAck);
			}
			break;

			case MessageType::HeartbeatAck:
				Log(*socket, "Unauthorised heartbeat ACK");
				break;
			}

			receiving = true;
		}
		break;

		case sf::Socket::Disconnected:
			Disconnect();
			break;

		default:
			break;
		}
	}

	if (heartbeatTimer.getElapsedTime().asMilliseconds() > (HeartbeatThresholdMs + 1000))
	{
		Disconnect();
	}
}

bool User::IsConnected() const
{
	return connected;
}

void User::Disconnect()
{
	Log(*socket, "Disconnected");

	socket->disconnect();

	connected = false;
}