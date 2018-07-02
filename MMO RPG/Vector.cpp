#include <SFML/System/Vector2.hpp>

#include <valarray>

void normalize(sf::Vector2f& vector)
{
	const float hypotenuse = std::sqrt(vector.x * vector.x + vector.y * vector.y);

	if (vector.x != 0)
	{
		vector.x /= hypotenuse;
	}

	if (vector.y != 0)
	{
		vector.y /= hypotenuse;
	}
}