#include "ResourceManager.h"

#include <filesystem>

template<typename T, typename TResourceType>
std::map<std::string, T> ResourceManager<T, TResourceType>::resourceMap = LoadResources();

template<typename T, typename TResourceType>
const T& ResourceManager<T, TResourceType>::Get(const std::string& name)
{
	return resourceMap.at(name);
}

template<typename T, typename TResourceType>
std::map<std::string, T> ResourceManager<T, TResourceType>::LoadResources()
{
	std::map<std::string, T> resourceMap;

	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator{ std::filesystem::current_path().string() + "\\" + TResourceType::Folder })
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

template class ResourceManager<sf::Texture, ResourceManagement::Texture>;
template class ResourceManager<sf::Font, ResourceManagement::Font>;