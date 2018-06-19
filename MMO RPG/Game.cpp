#include "Game.h"
#include "Map.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window }
{
	sf::Texture texture;
	texture.loadFromFile("mapTest.png");

	map.AddTexture(texture);
	map.AddSprite(23, 16, 16);
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
}

void Game::ComposeFrame()
{
	map.Draw(gfx);
	player.Draw(gfx);
}