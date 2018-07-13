#include "HudWindow.h"

HudWindow::HudWindow()
	:
	opened{ false }
{
}

void HudWindow::ToggleOpened()
{
	opened = !opened;
}