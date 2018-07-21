#include "HudWindow.h"

#include "EventManager.h"

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

void HudWindow::Update()
{
	OnUpdate();
}

void HudWindow::Draw(const Graphics& gfx)
{
	OnDraw(gfx);
}

void HudWindow::CheckOpened()
{
	for (const sf::Event& event : EventManager::Query(sf::Event::EventType::KeyPressed))
	{
		if (event.key.code == toggleOpenKey)
		{
			ToggleOpened();
		}
	}
}

bool HudWindow::IsOpened() const
{
	return opened;
}

void HudWindow::OnUpdate()
{
}

void HudWindow::OnDraw(const Graphics& gfx)
{
}