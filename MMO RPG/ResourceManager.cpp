#include "ResourceManager.h"

#include <filesystem>
#include <unordered_map>

template<typename T, typename TResourceType>
std::unordered_map<std::string, T> ResourceManager<T, TResourceType>::resourceMap;

template<typename T, typename TResourceType>
const T& ResourceManager<T, TResourceType>::Get(const std::string& name)
{
	const auto iterator = resourceMap.find(name);

	if (iterator == resourceMap.end())
	{
		const std::string filename = std::filesystem::current_path().string() + "\\" + TResourceType::Folder + "\\" + name + TResourceType::Extension;

		T resource;

		if (!resource.loadFromFile(filename))
		{
			throw std::runtime_error{ "Could not load resource " + name };
		}

		return resourceMap.emplace(filename.substr(0, filename.find_last_of('.')), resource).first->second;
	}

	return iterator->second;
}

template class ResourceManager<sf::Texture, ResourceManagement::Texture>;
template class ResourceManager<sf::Font, ResourceManagement::Font>;