#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class Graphics
{
public:
	explicit Graphics(sf::RenderWindow& window);

public:
	void Begin() const;
	void Render() const;
	void End() const;

public:
	void Add(sf::Drawable& drawable);
	void Remove(sf::Drawable& drawable);

public:
	static constexpr unsigned int ScreenWidth = 1366;
	static constexpr unsigned int ScreenHeight = 768;

	static constexpr unsigned int Framerate = 60;

private:
	sf::RenderWindow& _window;
	std::vector<sf::Drawable*> _buffer;
};