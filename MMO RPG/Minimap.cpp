#include "Minimap.h"

#include "Player.h"

Minimap::Minimap(const Camera & camera, const Map & map)
	:
	worldDimensions{ map.GetDimensions() },
	minimapView{ sf::FloatRect{ 0.0f, 0.0f, worldDimensions.x, worldDimensions.y } },
	//player{ player },
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

		gfx.DrawUnbound(characterArea);
	}

	{
		const sf::FloatRect viewArea = camera.GetViewArea();

		sf::RectangleShape playerSurround{ sf::Vector2f{ viewArea.width, viewArea.height } };

		playerSurround.setPosition(viewArea.left, viewArea.top);
		playerSurround.setFillColor(sf::Color::Transparent);
		playerSurround.setOutlineThickness(-15.0f);

		gfx.DrawUnbound(playerSurround);
	}

	{
		sf::RectangleShape surround{ worldDimensions };

		surround.setFillColor(sf::Color::Transparent);
		surround.setOutlineThickness(-15.0f);

		gfx.DrawUnbound(surround);
	}

	gfx.ResetView();
}

void Minimap::AddCharacter(Character& character)
{
	characters.push_back(&character);
}