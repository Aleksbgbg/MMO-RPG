#include "Subtitle.h"

Subtitle::Subtitle(Text& text)
	:
	text{ text }
{
}

void Subtitle::Update()
{
	OnUpdate();
}

void Subtitle::Draw(const Graphics& gfx, const sf::Vector2f position) const
{
	text.setPosition(position);
	gfx.Draw(text);
}

sf::FloatRect Subtitle::GetDimensions() const
{
	return text.getLocalBounds();
}

std::string Subtitle::GetText() const
{
	return text.getString();
}

void Subtitle::Setup() const
{
	text.setCharacterSize(24);

	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1.0f);

	const sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height);
}

void Subtitle::OnUpdate()
{
}