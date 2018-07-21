#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Graphics.h"

class HudWindow
{
public:
	explicit HudWindow(const sf::Keyboard::Key toggleOpenKey);

public:
	virtual ~HudWindow() = default;

	void Update();
	void Draw(const Graphics& gfx);

	void CheckOpened();
	bool IsOpened() const;

protected:
	virtual void OnUpdate();
	virtual void OnDraw(const Graphics& gfx);

private:
	void ToggleOpened();

private:
	sf::Keyboard::Key toggleOpenKey;

	bool opened;
};