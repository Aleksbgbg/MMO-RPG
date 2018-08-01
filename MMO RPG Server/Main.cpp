#include <SFML/Network.hpp>

#include <iostream>

#include <ServerInfo.h>

static void Unblock(sf::Socket& socket)
{
	socket.setBlocking(false);
}

int main()
{
	sf::TcpListener tcpListener{ };

	Unblock(tcpListener);

	if (tcpListener.listen(ServerPort) != sf::Socket::Done)
	{
		const std::string diagnostic = "TcpListener listening error.";

		std::cout << diagnostic << std::endl;

		throw std::runtime_error{ diagnostic };
	}

	std::cout << "Listening at " << ServerIp << " on port " << ServerPort << ".\n";

	while (true)
	{
		// TODO: Mainloop server function.
	}

	return 0;
}