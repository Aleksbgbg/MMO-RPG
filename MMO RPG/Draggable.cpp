#include "Draggable.h"

#include <SFML/Window/Event.hpp>

#include "EventManager.h"

Draggable::Draggable()
	:
	mouseClicked{ false },
	wasReleased{ false }
{
}

void Draggable::Update(const sf::Vector2f position)
{
	if (mouseClicked)
	{
		for (const sf::Event& movement : EventManager::Query(sf::Event::EventType::MouseMoved))
		{
			dragOffset = sf::Vector2f{ static_cast<float>(movement.mouseMove.x), static_cast<float>(movement.mouseMove.y) } - initialPosition;
		}

		CheckMouseClicked(sf::Event::EventType::MouseButtonReleased, false);
	}
	else
	{
		CheckMouseClicked(sf::Event::EventType::MouseButtonPressed, true);
		//CheckMouseClicked(sf::Event::EventType::MouseButtonReleased, false);

		if (!IsDragging())
		{
			initialPosition = position;
		}
	}
}

sf::Vector2f Draggable::GetPosition() const
{
	return initialPosition + dragOffset;
}

bool Draggable::IsDragging() const
{
	return mouseClicked && !(dragOffset.x == 0 || dragOffset.y == 0);
}

bool Draggable::WasReleased() const
{
	return wasReleased;
}

void Draggable::ConsumeRelease()
{
	wasReleased = false;
	dragOffset = sf::Vector2f{ 0.0f, 0.0f };
}

void Draggable::CheckMouseClicked(const sf::Event::EventType eventType, const bool mouseClickValue)
{
	for (const sf::Event& click : EventManager::Query(eventType))
	{
		if (click.mouseButton.button == sf::Mouse::Left && (!mouseClickValue || IsAt(sf::Vector2f{ static_cast<float>(click.mouseButton.x), static_cast<float>(click.mouseButton.y) })))
		{
			SetMouseClicked(mouseClickValue);
		}
	}
}

void Draggable::SetMouseClicked(const bool value)
{
	wasReleased = mouseClicked && !value;
	mouseClicked = value;
}