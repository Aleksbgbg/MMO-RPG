#include "Graphics.h"

Graphics::Graphics(sf::RenderWindow & window)
	:
	window{ window }
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

void Graphics::Draw(const sf::Sprite& sprite) const
{
	const sf::Vector2i spriteScreenPosition = window.mapCoordsToPixel(sprite.getPosition());
	const sf::FloatRect spriteGlobalBounds = sprite.getGlobalBounds();

	if (0 <= spriteScreenPosition.x + spriteGlobalBounds.width && spriteScreenPosition.x <= ScreenWidth &&
		0 <= spriteScreenPosition.y + spriteGlobalBounds.height && spriteScreenPosition.y <= ScreenHeight)
	{
		window.draw(sprite);
	}
}

void Graphics::DrawUnbound(const sf::Drawable& drawable) const
{
	window.draw(drawable);
}

void Graphics::ChangeView(const sf::View& view)
{
	lastView = sf::View{ window.getView() };
	window.setView(view);
}

void Graphics::ResetView() const
{
	window.setView(lastView);
}

sf::Vector2i Graphics::MapCoordsToPixel(const sf::Vector2f& point) const
{
	return window.mapCoordsToPixel(point);
}

sf::Vector2f Graphics::MapPixelToCoords(const sf::Vector2i& point) const
{
	return window.mapPixelToCoords(point);
}