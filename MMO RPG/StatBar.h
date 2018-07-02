#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Graphics.h"

class StatBar
{
public:
	explicit StatBar(const sf::Color color);

public:
	void Render(const Graphics& gfx, const float percentage, const sf::Vector2f position);

private:
	static constexpr float Width = 10.0f;
	static constexpr float Height = 3.0f;

private:
	sf::RectangleShape barRectangle;
};