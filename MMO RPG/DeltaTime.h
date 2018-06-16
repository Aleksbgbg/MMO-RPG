#pragma once

#include <SFML/System/Clock.hpp>

class DeltaTime
{
public:
	static float Get();

	static void Restart();
	
private:
	DeltaTime();

	static sf::Clock _clock;
};