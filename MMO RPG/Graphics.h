#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"

class Graphics
{
public:
	Graphics(sf::RenderWindow& window, const Camera camera);

public:
	void Begin() const;
	void End() const;

	void Draw(const sf::Sprite& sprite) const;

	Camera& GetCamera();

public:
	static constexpr int ScreenWidth = 1366;
	static constexpr int ScreenHeight = 768;

	static constexpr int Framerate = 60;

private:
	sf::RenderWindow& window;

	Camera camera;
};