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
	heartbeatAcknowledged{ true },
	heartbeatThresholdMs{ 0 }
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
		connected = serverSocket.connect(sf::IpAddress{ ServerIp }, ServerPort, sf::milliseconds(static_cast<sf::Uint32>(5000u))) == sf::Socket::Done;

		serverSocket.setBlocking(false);

		if (connected)
		{
			OutputDebugStringA("Connected\n");

			sf::Packet helloPacket{ };

			sf::Socket::Status handshakeStatus;

			do
			{
				handshakeStatus = Receive(serverSocket, helloPacket);
			} while (handshakeStatus == sf::Socket::NotReady);

			if (handshakeStatus != sf::Socket::Done)
			{
				OutputDebugStringA("Error in receiving handshake");
				Disconnect();
				continue;
			}

			int messageType;

			helloPacket >> messageType;

			if (static_cast<MessageType>(messageType) == MessageType::Hello)
			{
				helloPacket >> heartbeatThresholdMs;

				OutputDebugStringA(("Handshake completed; threshold " + std::to_string(heartbeatThresholdMs) + "ms\n").c_str());
			}
			else
			{
				OutputDebugStringA("Received non-handshake message when expecting handshake");
				Disconnect();
				continue;
			}
		}

		while (connected)
		{
			if (heartbeatTimer.getElapsedTime().asMilliseconds() > heartbeatThresholdMs)
			{
				sf::Packet heartbeat{ };

				heartbeat << static_cast<int>(MessageType::Heartbeat);

				if (!heartbeatAcknowledged)
				{
					OutputDebugStringA("No heartbeat ACK\n");
					Disconnect();
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
					Disconnect();
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

void ServerConnection::Disconnect()
{
	connected = false;
	serverSocket.disconnect();
	OutputDebugStringA("Disconnected");
}