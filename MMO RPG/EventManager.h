#pragma once

#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>

#include "TimeoutTracker.h"
#include "Graphics.h"

class EventManager
{
public:
	struct DoubleClick
	{
		bool didOccur;
		sf::Vector2i position;
	};

public:
	static EventManager& Make();

	static const std::vector<sf::Event>& Query(const sf::Event::EventType type);
	static DoubleClick GetDoubleClick();

public:
	void Update();

	void Register(const sf::Event& event);
	void Clear();

	const std::vector<sf::Event>& Find(const sf::Event::EventType type) const;

	DoubleClick DoubleClickGet() const;

private:
	EventManager() = default;

private:
	class DoubleClickChecker
	{
	public:
		DoubleClickChecker();

	public:
		void Update();

		DoubleClick GetDoubleClick() const;

	private:
		static constexpr int PixelLeeway = 8;

	private:
		TimeoutTracker timeoutTracker;
		int clickCount;
		sf::Vector2i position;
	};

private:
	static EventManager instance;
	static bool made;

private:
	std::vector<sf::Event>& Find(const sf::Event::EventType type);

private:
	std::map<sf::Event::EventType, std::vector<sf::Event>> events;

	DoubleClickChecker doubleClickChecker;
};