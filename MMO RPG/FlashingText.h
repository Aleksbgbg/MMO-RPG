#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Graphics.h"

class FlashingText
{
public:
	FlashingText(const std::string& string, const sf::Vector2i position);

public:
	void Update(const Graphics& gfx);
	void Draw(const Graphics& gfx) const;

private:
	static constexpr int AlphaModifierMagnitude = 3;

private:
	sf::Text text;

	sf::Vector2i position;

	int alpha;
	int alphaModifier;
};