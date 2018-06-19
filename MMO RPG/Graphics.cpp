#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow& window)
	:
	_window{ window }
{
	_window.setFramerateLimit(Framerate);
}

void Graphics::Begin() const
{
	_window.clear();
}

void Graphics::End() const
{
	_window.display();
}

void Graphics::Draw(const sf::Drawable& drawable) const
{
	_window.draw(drawable);
}