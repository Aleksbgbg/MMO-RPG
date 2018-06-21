#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <map>

class TextureManager
{
public:
	static const sf::Texture& Get(const std::string& name);

private:
	static std::map<std::string, sf::Texture> LoadTextures();

private:
	static std::map<std::string, sf::Texture> textureMap;
};