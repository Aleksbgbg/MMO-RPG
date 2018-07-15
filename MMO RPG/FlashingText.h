#pragma once

#include "Subtitle.h"

class FlashingText : public Subtitle
{
public:
	explicit FlashingText(const std::string& string);

public:
	void OnUpdate() override;

private:
	static constexpr int AlphaModifierMagnitude = 3;

private:
	Text text;

	int alpha;
	int alphaModifier;
};