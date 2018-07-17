#pragma once

#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>

class EventManager
{
public:
	static EventManager& Make();

	static const std::vector<sf::Event>& Query(const sf::Event::EventType type);

public:
	void Register(const sf::Event& event);
	void Clear();

	const std::vector<sf::Event>& Find(const sf::Event::EventType type) const;

private:
	EventManager() = default;

private:
	inline static bool made = false;
	static EventManager instance;

private:
	std::vector<sf::Event>& Find(const sf::Event::EventType type);

private:
	std::map<sf::Event::EventType, std::vector<sf::Event>> events;
};