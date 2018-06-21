#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Camera
{
public:
	Camera(sf::RenderWindow& window);

public:
	void UpdatePlayerPosition(sf::Vector2f playerPosition);

private:
	sf::RenderWindow& window;

	sf::Vector2f playerPosition;
};