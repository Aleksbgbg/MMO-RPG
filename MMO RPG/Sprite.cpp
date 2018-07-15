#include "Sprite.h"

Sprite::Sprite(const std::shared_ptr<sf::Texture>& texture)
	:
	sf::Sprite{ *texture },
	texture{ texture }
{
}

Sprite::Sprite(const std::shared_ptr<sf::Texture>& texture, const sf::IntRect& rectangle)
	:
	sf::Sprite{ *texture, rectangle },
	texture{ texture }
{
}