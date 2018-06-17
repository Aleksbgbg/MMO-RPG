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

void Graphics::Render() const
{
	for (const sf::Drawable* const drawable : _buffer)
	{
		_window.draw(*drawable);
	}
}

void Graphics::End() const
{
	_window.display();
}

void Graphics::Add(sf::Drawable& drawable)
{
	_buffer.push_back(&drawable);
}

void Graphics::Remove(sf::Drawable& drawable)
{
	_buffer.erase(std::remove(_buffer.begin(), _buffer.end(), &drawable), _buffer.end());
}