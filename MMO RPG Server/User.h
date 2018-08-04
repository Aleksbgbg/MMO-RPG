#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/System/Clock.hpp>

#include <memory>

class User
{
public:
	explicit User(std::unique_ptr<sf::TcpSocket> userSocket);

public:
	void Update();

	bool IsConnected() const;

private:
	void Disconnect();

private:
	std::unique_ptr<sf::TcpSocket> socket;

	sf::Clock heartbeatTimer;

	bool connected;
};