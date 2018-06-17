#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:
	_gfx{ window },
	_window{ window },
	_player{ _gfx }
{
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