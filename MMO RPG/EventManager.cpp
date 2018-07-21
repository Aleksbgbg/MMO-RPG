#include "EventManager.h"

std::shared_ptr<EventManager> EventManager::instance{ nullptr };

std::shared_ptr<EventManager> EventManager::Make(const sf::RenderWindow& window)
{
	if (instance != nullptr)
	{
		throw std::runtime_error{ "Cannot instantiate EventManager twice." };
	}

	instance = std::make_shared<EventManager>(window);

	return instance;
}

const std::vector<sf::Event>& EventManager::Query(const sf::Event::EventType type)
{
	return instance->Find(type);
}

EventManager::DoubleClick EventManager::GetDoubleClick()
{
	return instance->DoubleClickGet();
}

void EventManager::Update()
{
	doubleClickChecker.Update();
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

EventManager::EventManager(const sf::RenderWindow& window)
	:
	doubleClickChecker{ window }
{
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

EventManager::DoubleClick EventManager::DoubleClickGet() const
{
	return doubleClickChecker.GetDoubleClick();
}

EventManager::DoubleClickChecker::DoubleClickChecker(const sf::RenderWindow& window)
	:
	timeoutTracker{ 0.375f },
	clickCount{ 0 },
	window{ window }
{
}

void EventManager::DoubleClickChecker::Update()
{
	timeoutTracker.Update();

	if (timeoutTracker.TimedOut())
	{
		clickCount = 0;
	}

	for (const sf::Event& event : Query(sf::Event::MouseButtonReleased))
	{
		if (event.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (clickCount == 0)
			{
				++clickCount;
				timeoutTracker.Reset();

				position = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
			}
			else
			{
				const sf::Vector2i distance = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y } - position;

				if (std::abs(distance.x) < PixelLeeway && std::abs(distance.y) < PixelLeeway)
				{
					++clickCount;

					position.x += distance.x / 2;
					position.y += distance.y / 2;
				}
			}
		}
	}
}

EventManager::DoubleClick EventManager::DoubleClickChecker::GetDoubleClick() const
{
	return DoubleClick{ clickCount >= 2, position };
}