#include "Camera.h"
#include "Graphics.h"

Camera::Camera(sf::RenderWindow& window, const Map& map)
	:
	window{ window },
	map{ map }
{
}

void Camera::UpdatePlayerPosition(const sf::Vector2f playerPosition)
{
	sf::View windowView{ window.getView() };

	{
		sf::Vector2f viewCenter{ playerPosition };

		constexpr int halfWindowWidth = Graphics::ScreenWidth / 2;
		constexpr int halfWindowHeight = Graphics::ScreenHeight / 2;

		const sf::Vector2i mapDimensions = map.GetDimensions();

		const int cameraEdgeRight = mapDimensions.x - halfWindowWidth;
		const int cameraEdgeBottom = mapDimensions.y - halfWindowHeight;

		if (mapDimensions.x <= Graphics::ScreenWidth)
		{
			viewCenter.x = mapDimensions.x / 2.0f;
		}
		else if (viewCenter.x < halfWindowWidth)
		{
			viewCenter.x = static_cast<float>(halfWindowWidth);
		}
		else if (viewCenter.x > cameraEdgeRight)
		{
			viewCenter.x = static_cast<float>(cameraEdgeRight);
		}

		if (mapDimensions.y <= Graphics::ScreenHeight)
		{
			viewCenter.y = mapDimensions.y / 2.0f;
		}
		else if (viewCenter.y < halfWindowHeight)
		{
			viewCenter.y = static_cast<float>(halfWindowHeight);
		}
		else if (viewCenter.y > cameraEdgeBottom)
		{
			viewCenter.y = static_cast<float>(cameraEdgeBottom);
		}

		windowView.setCenter(viewCenter);
	}

	window.setView(windowView);

	this->playerPosition = playerPosition;
}