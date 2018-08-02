#include <Windows.h>

#include "ServerConnection.h"

#include <SFML/Network.hpp>

#include "../Network Shared/DataTransfer.h"
#include "../Network Shared/ServerInfo.h"
#include "../Network Shared/MessageType.h"

ServerConnection::ServerConnection()
	:
	running{ true },
	connected{ false },
	connectionThread{ &ServerConnection::Run, this },
	heartbeatAcknowledged{ true }
{
}

ServerConnection::~ServerConnection()
{
	running = false;
	connected = false;

	connectionThread.join();

	serverSocket.disconnect();
}

void ServerConnection::Run()
{
	while (running)
	{
		connected = serverSocket.connect(sf::IpAddress{ ServerIp }, ServerPort, sf::milliseconds(static_cast<sf::Uint32>(HeartbeatThresholdMs))) == sf::Socket::Done;

		serverSocket.setBlocking(false);

		if (connected)
		{
			OutputDebugStringA("Connected\n");

			sf::Packet helloPacket{ };

			while (Receive(serverSocket, helloPacket) != sf::Socket::Done)
			{
			}

			int messageType;

			helloPacket >> messageType;

			if (static_cast<MessageType>(messageType) == MessageType::Hello)
			{
				std::string message;

				helloPacket >> message;

				OutputDebugStringA((message + "\n").c_str());
			}
			else
			{
				OutputDebugStringA("Error in handshake");
				continue;
			}
		}

		while (connected)
		{
			// Half heartbeat time in order to ensure received on time
			if (heartbeatTimer.getElapsedTime().asMilliseconds() > HeartbeatThresholdMs)
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
}

bool ServerConnection::IsConnected() const
{
	return connected;
}