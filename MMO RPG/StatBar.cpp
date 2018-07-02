#include "StatBar.h"

#include <SFML/Graphics/RectangleShape.hpp>

StatBar::StatBar(const sf::Color color)
{
	barRectangle.setFillColor(color);
}

void StatBar::Render(const Graphics& gfx, const float percentage, const sf::Vector2f position)
{
	barRectangle.setPosition(position);

	const sf::Vector2f barSize{ Width * percentage, Height };

	barRectangle.setSize(barSize);
	barRectangle.setOrigin(barSize.x / 2.0f, barSize.y / 2.0f);

	gfx.Draw(barRectangle);
}