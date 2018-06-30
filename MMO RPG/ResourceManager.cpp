#include "ResourceManager.h"

#include <filesystem>

template<typename T>
std::map<std::string, T> ResourceManager<T>::resourceMap = LoadResources();

template<typename T>
const T& ResourceManager<T>::Get(const std::string& name)
{
	return resourceMap.at(name);
}

template<typename T>
std::map<std::string, T> ResourceManager<T>::LoadResources()
{
	std::map<std::string, T> resourceMap;

	std::string resourceFolder;

	if constexpr (std::is_same<T, sf::Texture>::value)
	{
		resourceFolder = std::string{ "Textures" };
	}
	else if constexpr (std::is_same<T, sf::Font>::value)
	{
		resourceFolder = std::string{ "Fonts" };
	}

	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator{ std::filesystem::current_path().string() + "\\" + resourceFolder })
	{
		const std::string filepath = entry.path().string();
		const std::string filename = entry.path().filename().string();

		T resource;

		if (!resource.loadFromFile(filepath))
		{
			throw std::runtime_error{ "Could not load resource " + filename };
		}

		resourceMap.emplace(filename.substr(0, filename.find_last_of('.')), resource);
	}

	return resourceMap;
}

template class ResourceManager<sf::Texture>;
template class ResourceManager<sf::Font>;