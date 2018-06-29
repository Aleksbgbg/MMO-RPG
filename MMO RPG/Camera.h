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
	void UpdatePosition(const sf::Vector2f playerPosition, const sf::Vector2i playerDimensions);
	void SwitchMode(const Mode mode);

	void MoveBy(sf::Vector2f movement);

	Mode GetMode() const;
	sf::FloatRect GetViewArea() const;

private:
	static constexpr float SemiFreeCameraEdgePercentage = 0.25f;

	static constexpr float CameraMovementMultiplier = 5.0f;

private:
	sf::RenderWindow& window;
	const Map& map;

	Mode mode;

	sf::Vector2f previousCameraCenter;
	sf::Vector2f previousPlayerPosition;
	sf::Vector2i previousPlayerDimensions;
};