#pragma once

#include <SFML/Graphics/Font.hpp>

#include <map>

class FontManager
{
public:
	static const sf::Font& Get(const std::string& name);

private:
	static std::map<std::string, sf::Font> LoadFonts();

private:
	static std::map<std::string, sf::Font> fontMap;
};