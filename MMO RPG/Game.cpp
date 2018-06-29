#include "Game.h"

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window },
	camera{ window, map },
	player{ camera },
	minimap{ camera, map }
{
	for (int index = 0; index < Worlds; ++index)
	{
		worlds.emplace_back(std::string{ "Map" + std::to_string(index) + ".json" }, map, player, camera, minimap);
	}

	ChangeActiveWorld(0);
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

	for (World& world : worlds)
	{
		world.Update();
	}

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
	{
		int nextWorld = currentActiveWorld + 1;

		if (nextWorld >= static_cast<int>(worlds.size()))
		{
			nextWorld = 0;
		}

		ChangeActiveWorld(nextWorld);
	}
}

void Game::ComposeFrame()
{
	map.Draw(gfx);

	activeWorld->Draw(gfx);

	player.Draw(gfx);

	minimap.Draw(gfx);
}

void Game::ChangeActiveWorld(const int index)
{
	activeWorld = &worlds[index];
	activeWorld->Activate();
	currentActiveWorld = index;
}