#include "Game.h"

#include <fstream>

using json = nlohmann::json;

Game::Game(sf::RenderWindow& window)
	:
	gfx{ window },
	camera{ window, map },
	player{ camera },
	minimap{ camera, map },
	teleportInstructionText{ std::string{ "Press X to teleport..." }, sf::Vector2i{ Graphics::ScreenWidth / 2, Graphics::ScreenHeight } },
	canTeleport{ false }
{
	json worldConfig;

	{
		std::ifstream input{ "World Config.json" };

		if (!input.is_open())
		{
			throw std::runtime_error{ "Cannot open file 'World Config.json'." };
		}

		worldConfig = json::parse(input);
	}

	for (int index = 0; index < Worlds; ++index)
	{
		worlds.emplace_back(std::string{ "Map" + std::to_string(index) + ".json" }, map, player, camera, minimap, worldConfig[index]);
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

	canTeleport = activeWorld->PlayerCanTeleport();

	if (canTeleport)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			const Portal& sourcePortal = activeWorld->FindNearestPortal();

			ChangeActiveWorld(sourcePortal.targetWorldIndex);
			player.TeleportTo(worlds[sourcePortal.targetWorldIndex].GetPortal(sourcePortal.targetPortalIndex));
		}
		else
		{
			teleportInstructionText.Update(gfx);
		}
	}
}

void Game::ComposeFrame()
{
	map.Draw(gfx);

	activeWorld->Draw(gfx);

	player.Draw(gfx);

	minimap.Draw(gfx);

	if (canTeleport && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
	{
		teleportInstructionText.Draw(gfx);
	}
}

void Game::ChangeActiveWorld(const int index)
{
	activeWorld = &worlds[index];
	activeWorld->Activate();
}