#include "DataTransfer.h"

#include <cassert>

static sf::Socket::Status Dispatch(sf::TcpSocket& socket, sf::Packet& packet, sf::Socket::Status (sf::TcpSocket::*dispatchFunc)(sf::Packet&))
{
	assert(!socket.isBlocking());
	
	while (true)
	{
		const sf::Socket::Status status = (socket.*dispatchFunc)(packet);

		if (status != sf::Socket::Partial)
		{
			return status;
		}
	}
}

sf::Socket::Status Send(sf::TcpSocket& socket, sf::Packet& packet)
{
	return Dispatch(socket, packet, &sf::TcpSocket::send);
}

sf::Socket::Status Receive(sf::TcpSocket& socket, sf::Packet& packet)
{
	return Dispatch(socket, packet, &sf::TcpSocket::receive);
}