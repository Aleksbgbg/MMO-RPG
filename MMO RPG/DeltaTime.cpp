#include "DeltaTime.h" 

sf::Clock DeltaTime::_clock;

float DeltaTime::_value{ 0 };

float DeltaTime::Get()
{
	return _value;
}

void DeltaTime::Restart()
{
	_value = _clock.restart().asSeconds();
}