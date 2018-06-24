#include "Game.h"
#include "Map.h"
#include "TextureManager.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window, Camera{ window, map } },
	camera{ gfx.GetCamera() },
	player{ gfx.GetCamera() }
{
	map.AddTexture(TextureManager::Get("Map"));
	map.AddAllSprites();

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 2; ++y)
		{
			npcs.push_back(std::make_unique<Npc>(sf::Vector2i{ x, y }, map));
		}
	}
}

void Game::Main()
{
	gfx.Begin();

	UpdateModel();
	ComposeFrame();

	gfx.End();
}

void Game::UpdateModel()
{
	player.Update();

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Update();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		camera.SwitchMode(Camera::Mode::Fixed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		camera.SwitchMode(Camera::Mode::SemiFree);
	}
}

void Game::ComposeFrame()
{
	map.Draw(gfx);
	player.Draw(gfx);

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Draw(gfx);
	}
}