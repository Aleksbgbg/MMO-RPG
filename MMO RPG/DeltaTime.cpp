#include "DeltaTime.h"

#include <stdexcept>

DeltaTime& DeltaTime::Make()
{
	if (made)
	{
		throw std::runtime_error{ "Cannot instantiate a second DeltaTime." };
	}

	made = true;

	return instance;
}

DeltaTime::DeltaTime()
	:
	value{ 0.0f }
{
}

float DeltaTime::Get()
{
	return instance.GetValue();
}

float DeltaTime::GetValue() const
{
	return value;
}

void DeltaTime::Restart()
{
	value = clock.restart().asSeconds();
}