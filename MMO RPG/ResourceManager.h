#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <map>

template<typename T>
class ResourceManager
{
public:
	static const T& Get(const std::string& name);

private:
	static std::map<std::string, T> LoadResources();

private:
	static std::map<std::string, T> resourceMap;
};

typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;