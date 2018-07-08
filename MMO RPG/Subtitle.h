#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Graphics.h"

class Subtitle
{
public:
	explicit Subtitle(sf::Text& text);

public:
	virtual ~Subtitle() = default;

public:
	void Update();
	void Draw(const Graphics& gfx, const sf::Vector2f position) const;

	sf::FloatRect GetDimensions() const;

	std::string GetText() const;

protected:
	void Setup() const;

	virtual void OnUpdate();

private:
	sf::Text& text;
};