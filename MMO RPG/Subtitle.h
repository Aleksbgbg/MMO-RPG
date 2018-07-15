#pragma once

#include "Graphics.h"
#include "Text.h"

class Subtitle
{
public:
	explicit Subtitle(Text& text);

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
	Text& text;
};