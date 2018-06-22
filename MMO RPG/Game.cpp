#include "Game.h"
#include "Map.h"
#include "TextureManager.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window, Camera{ window, map } },
	player{ gfx.GetCamera() }
{
	map.AddTexture(TextureManager::Get("mapTest"));
	map.AddAllSprites();

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 2; ++y)
		{
			npcs.push_back(std::make_unique<Npc>(sf::Vector2i{ x, y }));
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