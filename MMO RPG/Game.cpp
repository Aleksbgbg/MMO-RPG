#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window },
	camera{ window, map },
	world{ map, camera }
{
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
	world.Update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		camera.SwitchMode(Camera::Mode::Fixed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		camera.SwitchMode(Camera::Mode::SemiFree);
	}

	{
		sf::Vector2f cameraMovement;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			cameraMovement.x = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			cameraMovement.x = 1;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			cameraMovement.y = -1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			cameraMovement.y = 1;
		}

		if (!(cameraMovement.x == 0 && cameraMovement.y == 0))
		{
			camera.MoveBy(cameraMovement);
		}
	}
}

void Game::ComposeFrame()
{
	world.Draw(gfx);
}