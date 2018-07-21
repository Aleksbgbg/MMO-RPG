#include "Hud.h"

Hud::Hud(Player& player)
	:
	view{ sf::FloatRect{ 0.0f, 0.0f, static_cast<float>(Graphics::ScreenWidth), static_cast<float>(Graphics::ScreenHeight) } }
{
	windows.emplace_back(std::make_unique<Inventory>(player));
}

void Hud::Draw(Graphics& gfx)
{
	gfx.ChangeView(view);

	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		window->Draw(gfx);
	}

	gfx.ResetView();
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