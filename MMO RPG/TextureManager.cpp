#include "TextureManager.h"

#include <filesystem>

const sf::Texture& TextureManager::Get(const std::string& name)
{
	return textureMap.at(name);
}

std::map<std::string, sf::Texture> TextureManager::LoadTextures()
{
	std::map<std::string, sf::Texture> textureMap;

	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator{ std::filesystem::current_path().string() + "\\Textures" })
	{
		const std::string filepath = entry.path().string();
		const std::string filename = entry.path().filename().string();

		sf::Texture texture;

		if (!texture.loadFromFile(filepath))
		{
			throw std::runtime_error{ "Could not load texture " + filename };
		}

		textureMap.emplace(filename.substr(0, filename.find_last_of('.')), texture);
	}

	return textureMap;
}