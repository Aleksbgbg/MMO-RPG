#include <SFML/Graphics.hpp>

#include <windows.h>

#include "DeltaTime.h"
#include "Game.h"
#include "EventManager.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
	sf::RenderWindow window{ sf::VideoMode{ static_cast<unsigned int>(Graphics::ScreenWidth), static_cast<unsigned int>(Graphics::ScreenHeight) }, "MMO RPG", sf::Style::Titlebar | sf::Style::Close };

	window.setFramerateLimit(Graphics::Framerate);

	Game game{ window };

	DeltaTime& deltaTime = DeltaTime::Make();
	EventManager& eventManager = EventManager::Make();

	while (window.isOpen())
	{
		{
			sf::Event event{ };

			while (window.pollEvent(event))
			{
				eventManager.Register(event);

				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					game.KeyPressed(event.key.code);
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					game.MouseClicked(window.mapPixelToCoords(sf::Vector2i{ event.mouseButton.x, event.mouseButton.y }));
				}
			}
		}

		game.Main();
		
		eventManager.Clear();

		deltaTime.Restart();
	}

	return 0;
}