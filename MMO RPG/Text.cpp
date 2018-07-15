#include "Text.h"

Text::Text(const sf::String& string, const std::shared_ptr<sf::Font>& font, const unsigned int characterSize)
	:
	sf::Text{ string, *font, characterSize },
	font{ font }
{
}