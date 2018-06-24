#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow& window, const Camera camera)
	:
	window{ window },
	camera{ camera }
{
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