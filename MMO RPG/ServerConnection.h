#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Clock.hpp>

#include <thread>

class ServerConnection
{
public:
	ServerConnection();

public:
	~ServerConnection();

public:
	ServerConnection(const ServerConnection&) = delete;
	ServerConnection(ServerConnection&&) = delete;

	ServerConnection& operator=(const ServerConnection&) = delete;
	ServerConnection& operator=(ServerConnection&&) = delete;

public:
	void Update();

	bool IsConnected() const;

private:
	sf::TcpSocket serverSocket;

	bool connected;

	std::thread updateThread;

	sf::Clock heartbeatTimer;

	bool heartbeatAcknowledged;
};