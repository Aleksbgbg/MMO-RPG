#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game(Game&) = delete;
	Game(Game&&) = delete;

	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

private:
	sf::RenderWindow& _window;
};