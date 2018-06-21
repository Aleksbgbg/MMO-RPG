#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow& window)
	:
	window{ window },
	camera{ window }
{
	window.setFramerateLimit(Framerate);
}

void Graphics::Begin() const
{
	window.clear();
}

void Graphics::End() const
{
	window.display();
}

void Graphics::Draw(const sf::Drawable& drawable) const
{
	window.draw(drawable);
}

Camera& Graphics::GetCamera()
{
	return camera;
}