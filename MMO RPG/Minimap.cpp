#include "Minimap.h"

#include "Player.h"

Minimap::Minimap(const Camera & camera, const Map & map)
	:
	worldDimensions{ map.GetDimensions() },
	minimapView{ sf::FloatRect{ 0.0f, 0.0f, worldDimensions.x, worldDimensions.y } },
	camera{ camera }
{
	minimapView.setViewport(sf::FloatRect{ 0.900f, 0.0f, 0.100f, 0.125f });
}

void Minimap::Draw(Graphics& gfx) const
{
	gfx.ChangeView(minimapView);

	for (const Character* const character : characters)
	{
		sf::RectangleShape characterArea{ sf::Vector2f{ 50.0f, 50.0f } };

		if (dynamic_cast<const Player* const>(character) == nullptr)
		{
			characterArea.setFillColor(sf::Color{ 220, 220, 220 });
		}
		else
		{
			characterArea.setFillColor(sf::Color::Red);
		}

		characterArea.setPosition(character->GetPosition());

		gfx.Draw(characterArea);
	}

	{
		const sf::FloatRect viewArea = camera.GetViewArea();

		sf::RectangleShape playerViewBorder{ sf::Vector2f{ viewArea.width, viewArea.height } };

		playerViewBorder.setPosition(viewArea.left, viewArea.top);
		playerViewBorder.setFillColor(sf::Color::Transparent);
		playerViewBorder.setOutlineThickness(-15.0f);

		gfx.Draw(playerViewBorder);
	}

	{
		sf::RectangleShape mapBorder{ worldDimensions };

		mapBorder.setFillColor(sf::Color::Transparent);
		mapBorder.setOutlineThickness(-15.0f);

		gfx.Draw(mapBorder);
	}

	gfx.ResetView();
}

void Minimap::LoadNewWorld(const sf::Vector2f newWorldDimensions)
{
	characters.clear();

	worldDimensions = newWorldDimensions;

	minimapView.setCenter(worldDimensions.x / 2.0f, worldDimensions.y / 2.0f);
	minimapView.setSize(worldDimensions);
}

void Minimap::AddCharacter(Character& character)
{
	characters.push_back(&character);
}