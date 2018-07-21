#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

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
	void Update(const sf::Vector2f position);

	virtual bool IsAt(const sf::Vector2f position) const = 0;

private:
	void CheckMouseClicked(const sf::Event::EventType eventType, const bool mouseClickValue);
	void SetMouseClicked(const bool value);

private:
	bool mouseClicked;
	bool wasReleased;

	sf::Vector2f initialPosition;
	sf::Vector2f dragOffset;
};