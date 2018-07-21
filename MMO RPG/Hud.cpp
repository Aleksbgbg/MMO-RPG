#include "Hud.h"

Hud::Hud(Player& player)
	:
	view{ sf::FloatRect{ 0.0f, 0.0f, static_cast<float>(Graphics::ScreenWidth), static_cast<float>(Graphics::ScreenHeight) } }
{
	windows.emplace_back(std::make_unique<Inventory>(player));
}

void Hud::Update()
{
	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		window->CheckOpened();

		if (window->IsOpened())
		{
			window->Update();
		}
	}
}

void Hud::Draw(Graphics& gfx)
{
	gfx.ChangeView(view);

	for (const std::unique_ptr<HudWindow>& window : windows)
	{
		if (window->IsOpened())
		{
			window->Draw(gfx);
		}
	}

	gfx.ResetView();
}