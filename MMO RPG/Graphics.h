#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Graphics
{
public:
	explicit Graphics(sf::RenderWindow& window);

public:
	void Begin() const;
	void End() const;

	void Draw(const sf::Sprite& sprite) const;
	void DrawUnbound(const sf::Drawable& drawable) const;

	void ChangeView(const sf::View& view);
	void ResetView() const;

public:
	static constexpr int ScreenWidth = 1366;
	static constexpr int ScreenHeight = 768;

	static constexpr int Framerate = 60;

private:
	sf::RenderWindow& window;

	sf::View lastView;
};