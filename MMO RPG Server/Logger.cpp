#include "Logger.h"

#include <iostream>
#include <iomanip>

void Log(const sf::TcpSocket& playerSocket, const std::string& message)
{
	const auto time = std::time(nullptr);

	std::cout << "[" << std::put_time(std::localtime(&time), "%d/%m/%Y %H:%M:%S") << "] "
		<< "(" << playerSocket.getRemoteAddress() << ":" << playerSocket.getRemotePort() << ") "
		<< message
		<< std::endl;
}