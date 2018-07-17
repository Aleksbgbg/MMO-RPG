#pragma once


#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include "Graphics.h"

class Draggable
{
public:
	Draggable();

public:
	virtual ~Draggable() = default;

public:
	sf::Vector2f GetPosition() const;

	bool IsDragging() const;
	bool WasReleased() const;

	void ConsumeRelease();

protected:
	void Update(const Graphics& gfx, const sf::Vector2f position);

	virtual bool IsAt(const sf::Vector2f position) const = 0;

private:
	void CheckDragging(const Graphics& gfx, const sf::Event::EventType eventType, const bool draggingValue);
	void SetDragging(const bool value);

private:
	bool dragging;
	bool wasReleased;

	sf::Vector2f initialPosition;
	sf::Vector2f dragOffset;
};