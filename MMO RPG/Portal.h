#pragma once

#include <SFML/Graphics/Rect.hpp>

struct Portal
{
public:
	Portal(const sf::FloatRect occupation, const int targetWorldIndex, const int targetPortalIndex);

public:
	const sf::FloatRect occupation;
	const int targetWorldIndex;
	const int targetPortalIndex;
};