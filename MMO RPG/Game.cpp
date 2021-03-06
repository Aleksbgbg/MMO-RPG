#include "Game.h"

#include "Json.h"
#include "ResourceManager.h"

using nlohmann::json;

Game::Game(sf::RenderWindow& window)
	:
	window{ window },
	gfx{ window },
	camera{ window, map },
	player{ camera },
	minimap{ camera, map },
	activeWorld{ nullptr },
	canTeleport{ false },
	reticleTarget{ nullptr },
	hud{ player }
{
	json worldConfig = read_json("Config\\World.json");

	for (int index = 0; index < Worlds; ++index)
	{
		worlds.emplace_back(std::string{ "Map" + std::to_string(index) + ".json" }, map, player, minimap, worldConfig[index]);
	}

	ChangeActiveWorld(1);
}

void Game::Main()
{
	gfx.Begin();

	UpdateModel();
	ComposeFrame();

	gfx.End();
}

void Game::KeyPressed(const sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::X && canTeleport)
	{
		const Portal& sourcePortal = activeWorld->FindNearestPortal();

		ChangeActiveWorld(sourcePortal.targetWorldIndex);
		player.TeleportTo(worlds[sourcePortal.targetWorldIndex].GetPortal(sourcePortal.targetPortalIndex));
	}
	else if (key == sf::Keyboard::Key::Q && reticleTarget != nullptr)
	{
		if (player.IsWithinRange(*reticleTarget.get()))
		{
			activeWorld->SpawnProjectile(Projectile{ TextureManager::Get("Fireball"), player.GetPosition(), reticleTarget });
		}
		else
		{
			subtitleHandler.Emplace(SubtitleHandler::SubtitleType::Warning, "Out of range!", 1.0f);
		}
	}
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		const std::shared_ptr<InteractiveCharacter> targetCharacter = std::dynamic_pointer_cast<InteractiveCharacter>(activeWorld->GetCharacter(sf::Vector2f{ gfx.MapPixelToCoords(sf::Mouse::getPosition(window)) }));

		if (targetCharacter != nullptr)
		{
			reticleTarget = targetCharacter;
		}
	}

	if (!activeWorld->CharacterExists(reticleTarget))
	{
		reticleTarget = nullptr;
	}

	if (reticleTarget != nullptr)
	{
		reticle.Update(*reticleTarget);
	}

	canTeleport = activeWorld->PlayerCanTeleport();

	if (canTeleport)
	{
		subtitleHandler.Emplace(SubtitleHandler::SubtitleType::Action, "Press X to teleport...");
	}
	else
	{
		subtitleHandler.Remove(SubtitleHandler::SubtitleType::Action);
	}

	subtitleHandler.Update();

	hud.Update();
}

void Game::ComposeFrame()
{
	map.Draw(gfx);

	activeWorld->Draw(gfx);

	player.Draw(gfx);

	if (reticleTarget != nullptr)
	{
		reticle.Draw(gfx);
	}

	hud.Draw(gfx);

	subtitleHandler.Draw(gfx);
}

void Game::ChangeActiveWorld(const int index)
{
	World* newWorld = &worlds[index];

	if (newWorld == activeWorld)
	{
		return;
	}

	reticleTarget = nullptr;

	activeWorld = newWorld;
	activeWorld->Activate();
}