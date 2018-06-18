#pragma once

#include <SFML/System/Clock.hpp>

class DeltaTime
{
public:
	static DeltaTime& Make();

	static float Get();

private:
	static DeltaTime _instance;
	static bool _made;

public:
	DeltaTime(DeltaTime&) = delete;
	DeltaTime(DeltaTime&&) = delete;

	DeltaTime operator=(DeltaTime&) = delete;
	DeltaTime operator=(DeltaTime&&) = delete;

public:
	void Restart();
	
private:
	DeltaTime();

private:
	float GetValue() const;

private:
	sf::Clock _clock;
	float _value;
};