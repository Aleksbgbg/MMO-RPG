#include <Windows.h>

#include "ServerConnection.h"

#include <SFML/Network.hpp>

#include "../Network Shared/DataTransfer.h"
#include "../Network Shared/ServerInfo.h"
#include "../Network Shared/MessageType.h"

ServerConnection::ServerConnection()
	:
	heartbeatAcknowledged{ true }
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

			heartbeat << static_cast<int>(MessageType::Heartbeat);

			if (!heartbeatAcknowledged)
			{
				// TODO:
				// Disconnected from server
				// Try to re-establish connection

				connected = false;
				OutputDebugStringA("No heartbeat ACK\n");
				return;
			}

			if (Send(serverSocket, heartbeat) == sf::Socket::Done)
			{
				heartbeatTimer.restart();
				heartbeatAcknowledged = false;
			}
		}

		bool receiving = true;

		while (receiving)
		{
			receiving = false;

			sf::Packet message{ };

			switch (Receive(serverSocket, message))
			{
			case sf::Socket::Done:
			{
				int messageType;

				message >> messageType;

				switch (static_cast<MessageType>(messageType))
				{
				case MessageType::HeartbeatAck:
					heartbeatAcknowledged = true;
					OutputDebugStringA("Heartbeat acknowledged\n");
					break;
				}

				receiving = true;
			}
			break;

			case sf::Socket::Disconnected:
				// TODO:
				// Disconnected from server
				// Try to re-establish connection

				connected = false;
				OutputDebugStringA("Disconnected\n");
				break;

			default:
				break;
			}
		}
	}
}

bool ServerConnection::IsConnected() const
{
	return connected;
}