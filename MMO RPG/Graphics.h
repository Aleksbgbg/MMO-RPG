#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Graphics
{
public:
	explicit Graphics(sf::RenderWindow& window);

public:
	void Begin() const;
	void End() const;

	template<typename T>
	void Draw(const T& drawable) const
	{
		const sf::Vector2i screenPosition = window.mapCoordsToPixel(drawable.getPosition());
		const sf::FloatRect globalBounds = drawable.getGlobalBounds();

		if (0 <= screenPosition.x + globalBounds.width && screenPosition.x <= ScreenWidth &&
			0 <= screenPosition.y + globalBounds.height && screenPosition.y <= ScreenHeight)
		{
			window.draw(drawable);
		}
	}
	void DrawUnbound(const sf::Drawable& drawable) const;

	void ChangeView(const sf::View& view);
	void ResetView() const;

	sf::Vector2i MapCoordsToPixel(const sf::Vector2f& point) const;
	sf::Vector2f MapPixelToCoords(const sf::Vector2i& point) const;

public:
	static constexpr int ScreenWidth = 1366;
	static constexpr int ScreenHeight = 768;

	static constexpr int Framerate = 60;

private:
	sf::RenderWindow& window;

	sf::View lastView;
};