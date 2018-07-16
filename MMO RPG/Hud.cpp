#include "Hud.h"

Hud::Hud(Player& player)
{
	windows.emplace_back(std::make_unique<Inventory>(player));
}

void Hud::Draw(const Graphics& gfx)
{
	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		window->Draw(gfx);
	}
}

void Hud::KeyPressed(const sf::Keyboard::Key key)
{
	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		window->KeyPressed(key);
	}
}

void Hud::MouseClicked(const sf::Vector2f position)
{
	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		window->MouseClicked(position);
	}
}