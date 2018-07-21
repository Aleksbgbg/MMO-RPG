#pragma once

#include <SFML/Window/Event.hpp>

#include <map>
#include <vector>

#include "TimeoutTracker.h"
#include "Graphics.h"

class EventManager
{
public:
	explicit EventManager(const sf::RenderWindow& window);

public:
	struct DoubleClick
	{
	public:
		DoubleClick(const bool didOccur, const sf::Vector2i position);

	public:
		bool didOccur;
		sf::Vector2i position;
	};

public:
	static std::shared_ptr<EventManager> Make(const sf::RenderWindow& window);

	static const std::vector<sf::Event>& Query(const sf::Event::EventType type);
	static DoubleClick GetDoubleClick();

public:
	void Update();

	void Register(const sf::Event& event);
	void Clear();

	const std::vector<sf::Event>& Find(const sf::Event::EventType type) const;

	DoubleClick DoubleClickGet() const;

private:
	class DoubleClickChecker
	{
	public:
		explicit DoubleClickChecker(const sf::RenderWindow& window);

	public:
		void Update();

		DoubleClick GetDoubleClick() const;

	private:
		static constexpr int PixelLeeway = 8;

	private:
		TimeoutTracker timeoutTracker;
		int clickCount;
		sf::Vector2i position;

		const sf::RenderWindow& window;
	};

private:
	static std::shared_ptr<EventManager> instance;

private:
	std::vector<sf::Event>& Find(const sf::Event::EventType type);

private:
	std::map<sf::Event::EventType, std::vector<sf::Event>> events;

	DoubleClickChecker doubleClickChecker;
};