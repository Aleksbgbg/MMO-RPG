#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <filesystem>
#include <unordered_map>

#include "Texture.h"
#include "Font.h"
#include "Shader.h"

template<typename T, typename TResourceType>
class ResourceManager
{
public:
	static std::shared_ptr<T> Get(const std::string& name)
	{
		return Get<>(name);
	}

	template<typename... TArgs>
	static std::shared_ptr<T> Get(const std::string& name, TArgs... loadArgs)
	{
		std::unordered_map<std::string, std::shared_ptr<T>>& resourceMap = GetResourceMap();

		const auto iterator = resourceMap.find(name);

		if (iterator == resourceMap.end())
		{
			const std::string filename = std::filesystem::current_path().string() + "\\" + TResourceType::Folder + "\\" + name + TResourceType::Extension;

			std::shared_ptr<T> resource = std::make_shared<T>();

			if (!resource->loadFromFile(filename, loadArgs...))
			{
				throw std::runtime_error{ "Could not load resource " + name };
			}

			return resourceMap.emplace(filename.substr(0, filename.find_last_of('.')), resource).first->second;
		}

		return iterator->second;
	}

private:
	static std::unordered_map<std::string, std::shared_ptr<T>>& GetResourceMap()
	{
		static std::unordered_map<std::string, std::shared_ptr<T>> resourceMap;

		return resourceMap;
	}
};

typedef ResourceManager<sf::Texture, ResourceManagement::Texture> TextureManager;
typedef ResourceManager<sf::Font, ResourceManagement::Font> FontManager;
typedef ResourceManager<sf::Shader, ResourceManagement::Shader> ShaderManager;