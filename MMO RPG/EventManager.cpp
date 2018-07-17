#include "EventManager.h"

EventManager& EventManager::Make()
{
	if (made)
	{
		throw std::runtime_error{ "Cannot instantiate EventManager twice." };
	}

	made = true;

	return instance;
}

const std::vector<sf::Event>& EventManager::Query(const sf::Event::EventType type)
{
	return instance.Find(type);
}

void EventManager::Register(const sf::Event& event)
{
	Find(event.type).push_back(event);
}

void EventManager::Clear()
{
	for (auto& event : events)
	{
		event.second.clear();
	}
}

const std::vector<sf::Event>& EventManager::Find(const sf::Event::EventType type) const
{
	return Find(type);
}

std::vector<sf::Event>& EventManager::Find(const sf::Event::EventType type)
{
	const auto iterator = events.find(type);

	if (iterator == events.end())
	{
		return events.emplace(type, std::vector<sf::Event>{ }).first->second;
	}

	return iterator->second;
}