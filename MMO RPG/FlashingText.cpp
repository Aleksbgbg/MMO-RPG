#include "FlashingText.h"

FlashingText::FlashingText(const std::string& string)
	:
	Subtitle{ text },
	text{ string, FontManager::Get("arial") },
	alpha{ 255 },
	alphaModifier{ 0 }
{
	Setup();
}

void FlashingText::OnUpdate()
{
	if (alpha <= 0)
	{
		alphaModifier = AlphaModifierMagnitude;
	}
	else if (alpha >= 255)
	{
		alphaModifier = -AlphaModifierMagnitude;
	}

	alpha += alphaModifier;

	text.setFillColor(sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha) });
}