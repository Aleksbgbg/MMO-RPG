#include "HudWindow.h"

HudWindow::HudWindow(const sf::Keyboard::Key toggleOpenKey)
	:
	toggleOpenKey{ toggleOpenKey },
	opened{ false }
{
}

void HudWindow::ToggleOpened()
{
	opened = !opened;
}

void HudWindow::Draw(const Graphics& gfx)
{
	if (!opened)
	{
		OnDraw(gfx);
	}
}

void HudWindow::KeyPressed(const sf::Keyboard::Key key)
{
	if (key == toggleOpenKey)
	{
		ToggleOpened();
	}

	if (opened)
	{
		OnKeyPressed(key);
	}
}

void HudWindow::MouseClicked(const sf::Vector2f position)
{
	if (opened)
	{
		OnMouseClicked(position);
	}
}

void HudWindow::OnDraw(const Graphics& gfx)
{
}

void HudWindow::OnKeyPressed(const sf::Keyboard::Key key)
{
}

void HudWindow::OnMouseClicked(const sf::Vector2f position)
{
}