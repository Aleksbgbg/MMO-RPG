#pragma once

#include <SFML/System/Clock.hpp>

class DeltaTime
{
public:
	static float Get();

	static void Restart();
	
private:
	DeltaTime();

private:
	static sf::Clock _clock;
	static float _value;
};