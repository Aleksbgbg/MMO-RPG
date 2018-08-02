#include "ServerConnection.h"

#include <SFML/Network.hpp>

#include "../Network Shared/ServerInfo.h"
#include "../Network Shared/MessageType.h"

ServerConnection::ServerConnection()
{
	connected = serverSocket.connect(sf::IpAddress{ ServerIp }, ServerPort, sf::milliseconds(HeartbeatThresholdMs)) == sf::Socket::Done;

	serverSocket.setBlocking(false);

	if (connected)
	{
		updateThread = std::thread{ &ServerConnection::Update, this };

		// TODO: Handshake?
	}
}

ServerConnection::~ServerConnection()
{
	connected = false;

	updateThread.join();

	serverSocket.disconnect();
}

void ServerConnection::Update()
{
	while (connected)
	{
		// Half heartbeat time in order to ensure received on time
		if (heartbeatTimer.getElapsedTime().asMilliseconds() > (HeartbeatThresholdMs / 2.0f))
		{
			sf::Packet heartbeat{ };

			heartbeat << static_cast<int>(MessageType::HeartbeatAck);

			if (serverSocket.send(heartbeat) == sf::Socket::Done)
			{
				heartbeatTimer.restart();
			}
		}
	}
}

bool ServerConnection::IsConnected() const
{
	return connected;
}