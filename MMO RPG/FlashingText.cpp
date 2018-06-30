#include "FlashingText.h"

#include "ResourceManager.h"

FlashingText::FlashingText(const std::string& string, const sf::Vector2i position)
	:
	text{ sf::String{ string }, FontManager::Get("arial"), 24 },
	position{ position },
	alpha{ 255 },
	alphaModifier{ 0 }
{
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);

	const sf::FloatRect textBounds = text.getLocalBounds();

	text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height);
}

void FlashingText::Update(const Graphics& gfx)
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
	
	text.setPosition(gfx.MapPixelToCoords(position));
	text.setFillColor(sf::Color{ 255, 255, 255, static_cast<sf::Uint8>(alpha) });
}

void FlashingText::Draw(const Graphics& gfx) const
{
	gfx.DrawUnbound(text);
}