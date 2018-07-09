#pragma once

#include "Graphics.h"

class Hud
{
public:
	void Draw(const Graphics& gfx) const;

private:
	static constexpr int ItemSlots = 10;

	static constexpr int ItemSlotDimension = 20;

	static constexpr int ItemSlotsVerticalPosition = Graphics::ScreenHeight - Graphics::ScreenHeight / 3;
	static constexpr int ItemSlotsHorizontalStart = (Graphics::ScreenWidth / ItemSlotDimension - ItemSlots) * ItemSlotDimension / 2;
};