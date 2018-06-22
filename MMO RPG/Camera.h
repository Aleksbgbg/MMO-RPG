#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Map.h"

class Camera
{
public:
	enum class Mode
	{
		Fixed,
		SemiFree
	};

public:
	Camera(sf::RenderWindow& window, const Map& map);

public:
	void UpdatePlayerPosition(const sf::Vector2f playerPosition);
	void SwitchMode(const Mode mode);

private:
	sf::RenderWindow& window;
	const Map& map;

	Mode mode;

	sf::Vector2f previousCameraCenter;
	sf::Vector2f previousPlayerPosition;
};