#pragma once

#include <SFML/Graphics/Text.hpp>

class Text : public sf::Text
{
public:
	Text() = default;
	Text(const sf::String& string, const std::shared_ptr<sf::Font>& font, const unsigned int characterSize = 30);

private:
	std::shared_ptr<sf::Font> font;
};