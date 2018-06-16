#include <SFML/Graphics.hpp>

#include <windows.h>

#include "Game.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	sf::RenderWindow window{ sf::VideoMode{ 1366, 768 }, "MMO RPG" };

	Game game{ window };

	while (window.isOpen())
	{
		{
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
			}
		}

		window.clear();

		game.Main();

		window.display();
	}

	return 0;
}