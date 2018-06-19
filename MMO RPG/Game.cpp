#include "Game.h"
#include "Map.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window },
	player{ playerSprite }
{
	sf::Texture texture;
	texture.loadFromFile("mapTest.png");

	if (!playerSprite.loadFromFile("Player.png"))
	{
		throw std::runtime_error{ "Player spritesheet loading not successful." };
	}

	if (!npcsTexture.loadFromFile("NPCs.png"))
	{
		throw std::runtime_error{ "NPC spritesheet loading not successful." };
	}

	map.AddTexture(texture);
	map.AddSprite(23, 16, 16);

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