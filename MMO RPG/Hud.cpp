#include "Hud.h"

void Hud::Draw(const Graphics& gfx)
{
	inventory.Draw(gfx);
}

void Hud::KeyPressed(const sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::I:
		inventory.ToggleOpened();
	}
}