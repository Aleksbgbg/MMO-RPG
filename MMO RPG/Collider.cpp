#include "Collider.h"

bool are_overlapping(const sf::FloatRect& first, const sf::FloatRect& second)
{
	const int firstRight = first.left + first.width;
	const int firstBottom = first.top + first.height;

	const int secondRight = second.left + second.width;
	const int secondBottom = second.top + second.height;

	return first.left <= secondRight && second.left <= firstRight &&
		   first.top <= secondBottom && second.top <= firstBottom;
}

bool is_inside(const sf::FloatRect& bounds, const sf::FloatRect& source)
{
	return bounds.left <= source.left && source.left + source.width <= bounds.left + bounds.width &&
		   bounds.top <= source.top && source.top + source.height <= bounds.top + bounds.height;
}