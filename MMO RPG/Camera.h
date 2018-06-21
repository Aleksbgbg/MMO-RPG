#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Map.h"

class Camera
{
public:
	Camera(sf::RenderWindow& window, const Map& map);

public:
	void UpdatePlayerPosition(const sf::Vector2f playerPosition);

private:
	sf::RenderWindow& window;
	const Map& map;

	sf::Vector2f playerPosition;
};