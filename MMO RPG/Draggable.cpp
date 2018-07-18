#include "Draggable.h"

#include <SFML/Window/Event.hpp>

#include "EventManager.h"
#include "Graphics.h"

Draggable::Draggable()
	:
	mouseClicked{ false },
	wasReleased{ false }
{
}

void Draggable::Update(const Graphics& gfx, const sf::Vector2f position)
{
	if (mouseClicked)
	{
		for (const sf::Event& movement : EventManager::Query(sf::Event::EventType::MouseMoved))
		{
			dragOffset = gfx.MapPixelToCoords(sf::Vector2i{ movement.mouseMove.x, movement.mouseMove.y }) - initialPosition;
		}

		CheckMouseClicked(gfx, sf::Event::EventType::MouseButtonReleased, false);
	}
	else
	{
		CheckMouseClicked(gfx, sf::Event::EventType::MouseButtonPressed, true);
		//CheckMouseClicked(gfx, sf::Event::EventType::MouseButtonReleased, false);

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

void Draggable::CheckMouseClicked(const Graphics& gfx, const sf::Event::EventType eventType, const bool mouseClickValue)
{
	for (const sf::Event& click : EventManager::Query(eventType))
	{
		if (click.mouseButton.button == sf::Mouse::Left && (!mouseClickValue || IsAt(gfx.MapPixelToCoords(sf::Vector2i{ click.mouseButton.x, click.mouseButton.y }))))
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