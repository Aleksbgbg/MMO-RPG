#include "DeltaTime.h" 

sf::Clock DeltaTime::_clock;

float DeltaTime::Get()
{
	return _clock.getElapsedTime().asSeconds();
}

void DeltaTime::Restart()
{
	_clock.restart();
}