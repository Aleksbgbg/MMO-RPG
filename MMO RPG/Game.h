#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Graphics.h"
#include "World.h"
#include "Minimap.h"
#include "Reticle.h"
#include "SubtitleHandler.h"
#include "Hud.h"

class Game
{
public:
	explicit Game(sf::RenderWindow& window);

	void Main();

	void KeyPressed(const sf::Keyboard::Key key);
	void MouseClicked(const sf::Vector2f position);

private:
	void UpdateModel();
	void ComposeFrame();

	void ChangeActiveWorld(const int index);

private:
	static constexpr int Worlds = 2;

private:
	sf::RenderWindow& window;
	Graphics gfx;

	Camera camera;

	Player player;

	Map map;

	Minimap minimap;

	World* activeWorld;

	std::vector<World> worlds;

	bool canTeleport;

	Reticle reticle;
	std::shared_ptr<InteractiveCharacter> reticleTarget;

	SubtitleHandler subtitleHandler;

	Hud hud;
};
