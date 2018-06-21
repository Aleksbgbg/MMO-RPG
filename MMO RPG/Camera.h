#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Camera
{
public:
	explicit Camera(sf::RenderWindow& window);

public:
	void UpdatePlayerPosition(const sf::Vector2f playerPosition);

private:
	sf::RenderWindow& window;

	sf::Vector2f playerPosition;
};