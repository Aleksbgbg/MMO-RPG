#include "DeltaTime.h"

#include <stdexcept>

DeltaTime DeltaTime::_instance{ };

bool DeltaTime::_made{ false };

DeltaTime DeltaTime::Make()
{
	if (_made)
	{
		throw std::runtime_error{ "Cannot instantiate a second DeltaTime." };
	}

	_made = true;

	return _instance;
}

DeltaTime::DeltaTime()
	:
	_value{ 0.0f }
{
}

float DeltaTime::Get()
{
	return _instance.GetValue();
}

float DeltaTime::GetValue() const
{
	return _value;
}

void DeltaTime::Restart()
{
	_value = _clock.restart().asSeconds();
}