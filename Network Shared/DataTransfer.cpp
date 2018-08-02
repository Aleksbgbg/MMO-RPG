#include "DataTransfer.h"

#include <cassert>

static sf::Socket::Status Dispatch(sf::Packet& packet, sf::Socket::Status (*dispatchFunc)(sf::Packet&))
{
	while (true)
	{
		const sf::Socket::Status status = dispatchFunc(packet);

		if (status != sf::Socket::Partial)
		{
			return status;
		}
	}
}

sf::Socket::Status Send(sf::TcpSocket& socket, sf::Packet& packet)
{
	assert(!socket.isBlocking());

	return Dispatch(packet, socket.send);
}

sf::Socket::Status Receive(sf::TcpSocket& socket, sf::Packet& packet)
{
	assert(!socket.isBlocking());

	return Dispatch(packet, socket.receive);
}