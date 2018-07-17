#include "Draggable.h"

#include <SFML/Window/Event.hpp>

#include "EventManager.h"
#include "Graphics.h"

Draggable::Draggable()
	:
	dragging{ false },
	wasReleased{ false }
{
}

void Draggable::Update(const Graphics& gfx, const sf::Vector2f position)
{
	if (dragging)
	{
		for (const sf::Event& movement : EventManager::Query(sf::Event::EventType::MouseMoved))
		{
			dragOffset = gfx.MapPixelToCoords(sf::Vector2i{ movement.mouseMove.x, movement.mouseMove.y }) - initialPosition;
		}

		CheckDragging(gfx, sf::Event::EventType::MouseButtonReleased, false);
	}
	else
	{
		CheckDragging(gfx, sf::Event::EventType::MouseButtonPressed, true);
		//CheckDragging(gfx, sf::Event::EventType::MouseButtonReleased, false);

		if (!dragging)
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
	return dragging;
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

void Draggable::CheckDragging(const Graphics& gfx, const sf::Event::EventType eventType, const bool draggingValue)
{
	for (const sf::Event& click : EventManager::Query(eventType))
	{
		if (click.mouseButton.button == sf::Mouse::Left && (!draggingValue || IsAt(gfx.MapPixelToCoords(sf::Vector2i{ click.mouseButton.x, click.mouseButton.y }))))
		{
			SetDragging(draggingValue);
		}
	}
}

void Draggable::SetDragging(const bool value)
{
	wasReleased = dragging && !value;
	dragging = value;
}