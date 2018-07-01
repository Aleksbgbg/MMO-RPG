#include "Collider.h"

bool is_inside(const sf::FloatRect& bounds, const sf::FloatRect& source)
{
	return bounds.left <= source.left && source.left + source.width <= bounds.left + bounds.width &&
		   bounds.top <= source.top && source.top + source.height <= bounds.top + bounds.height;
}