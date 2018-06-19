#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Graphics
{
public:
	explicit Graphics(sf::RenderWindow& window);

public:
	void Begin() const;
	void End() const;

	void Draw(const sf::Drawable& drawable) const;

public:
	static constexpr unsigned int ScreenWidth = 1366;
	static constexpr unsigned int ScreenHeight = 768;

	static constexpr unsigned int Framerate = 60;

private:
	sf::RenderWindow& window;
};