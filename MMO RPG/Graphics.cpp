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

Camera& Graphics::GetCamera()
{
	return camera;
}