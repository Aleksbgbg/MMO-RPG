#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <map>

class TextureManager : std::map<std::string, sf::Texture>
{
public:
	static const sf::Texture& Get(const std::string& name);

private:
	inline static TextureManager instance{ };

private:
	TextureManager();
};