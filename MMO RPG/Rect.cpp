#include "Rect.h"

sf::Vector2f center(const sf::FloatRect& rect)
{
	return sf::Vector2f{ rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f };
}