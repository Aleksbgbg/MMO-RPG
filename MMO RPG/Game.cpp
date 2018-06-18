#include "Game.h"
#include "Map.h"

Game::Game(sf::RenderWindow& window)
	:
	_gfx{ window },
	_window{ window },
	map{_gfx},
	_player{ _gfx }
{
	sf::Texture texture;
	texture.loadFromFile("mapTest.png");

	map.AddTexture(texture);
	map.AddSprite(23, 16, 16);
}

void Game::Main()
{
	_gfx.Begin();

	UpdateModel();
	ComposeFrame();

	_gfx.Render();
	_gfx.End();
}

void Game::UpdateModel()
{
	_player.Update();
}

void Game::ComposeFrame()
{
}