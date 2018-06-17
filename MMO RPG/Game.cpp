#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:
	_gfx{ window },
	_window{ window }
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
}

void Game::ComposeFrame()
{
}