#include "FontManager.h"

#include <filesystem>

std::map<std::string, sf::Font> FontManager::fontMap = LoadFonts();

const sf::Font& FontManager::Get(const std::string& name)
{
	return fontMap.at(name);
}

std::map<std::string, sf::Font> FontManager::LoadFonts()
{
	std::map<std::string, sf::Font> textureMap;

	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator{ std::filesystem::current_path().string() + "\\Fonts" })
	{
		const std::string filepath = entry.path().string();
		const std::string filename = entry.path().filename().string();

		sf::Font font;

		if (!font.loadFromFile(filepath))
		{
			throw std::runtime_error{ "Could not load font " + filename };
		}

		textureMap.emplace(filename.substr(0, filename.find_last_of('.')), font);
	}

	return textureMap;
}