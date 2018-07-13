#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include "Graphics.h"

class HudWindow
{
public:
	explicit HudWindow(const sf::Keyboard::Key toggleOpenKey);

public:
	virtual ~HudWindow() = default;

	void Draw(const Graphics& gfx);

	void KeyPressed(const sf::Keyboard::Key key);
	void MouseClicked(const sf::Vector2f position);

protected:
	virtual void OnDraw(const Graphics& gfx);

	virtual void OnKeyPressed(const sf::Keyboard::Key key);
	virtual void OnMouseClicked(const sf::Vector2f position);

private:
	void ToggleOpened();

private:
	sf::Keyboard::Key toggleOpenKey;

	bool opened;
};