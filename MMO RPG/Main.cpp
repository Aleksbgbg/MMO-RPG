#include <SFML/Graphics.hpp>

#include <windows.h>

#include "DeltaTime.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	sf::RenderWindow window{ sf::VideoMode{ Graphics::ScreenWidth, Graphics::ScreenHeight }, "MMO RPG" };

	Game game{ window };

	DeltaTime& deltaTime = DeltaTime::Make();

	while (window.isOpen())
	{
		{
			sf::Event event{ };

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::Resized)
				{
					window.setView(sf::View{ sf::FloatRect{ 0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height) } });
				}
			}
		}

		game.Main();

		deltaTime.Restart();
	}

	return 0;
}