#pragma once

class HudWindow
{
public:
	HudWindow();

public:
	virtual ~HudWindow() = default;

public:
	void ToggleOpened();

private:
	bool opened;
};