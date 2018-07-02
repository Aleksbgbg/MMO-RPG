#include "StatBar.h"

#include <SFML/Graphics/RectangleShape.hpp>

StatBar::StatBar(const sf::Color color)
{
	barRectangle.setFillColor(color);
}

void StatBar::Render(const Graphics& gfx, const float percentage, const sf::Vector2f position)
{
	barRectangle.setPosition(position);

	barRectangle.setSize(sf::Vector2f{ Width * percentage, Height });

	gfx.Draw(barRectangle);
}