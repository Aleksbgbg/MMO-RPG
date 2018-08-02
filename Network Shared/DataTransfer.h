#pragma once

#include <SFML/Network.hpp>

sf::Socket::Status Send(sf::TcpSocket& socket, sf::Packet& packet);

sf::Socket::Status Receive(sf::TcpSocket& socket, sf::Packet& packet);