#include "Game.h"
#include "Map.h"
#include "TextureManager.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window },
	player{ TextureManager::Get("Player") }
{
	map.AddTexture(TextureManager::Get("mapTest"));
	map.AddSprite(23, 16, 16);

	const sf::Texture& npcsTexture = TextureManager::Get("NPCs");

	for (int x = 0; x < 4; ++x)
	{
		for (int y = 0; y < 2; ++y)
		{
			npcs.push_back(std::make_unique<Npc>(sf::Vector2i{ x, y }, npcsTexture));
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