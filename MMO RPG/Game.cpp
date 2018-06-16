#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:
	_window{ window }
{
}

void Game::Main()
{
	UpdateModel();
	ComposeFrame();
}

void Game::UpdateModel()
{
}

void Game::ComposeFrame()
{
}