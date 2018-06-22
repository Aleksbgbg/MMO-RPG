#include "Camera.h"
#include "Graphics.h"

Camera::Camera(sf::RenderWindow& window, const Map& map)
	:
	window{ window },
	map{ map },
	mode{ Mode::Fixed }
{
}

void Camera::UpdatePlayerPosition(const sf::Vector2f playerPosition, const sf::Vector2i playerDimensions)
{
	sf::View windowView{ window.getView() };

	{
		sf::Vector2f newCameraCenter{ previousCameraCenter };

		const sf::Vector2f& viewCenter = windowView.getCenter();

		const sf::Vector2f playerScreenPosition{ playerPosition.x - (viewCenter.x - Graphics::ScreenWidth / 2) + playerDimensions.x / 2, playerPosition.y - (viewCenter.y - Graphics::ScreenHeight / 2) + playerDimensions.y / 2 };

		const sf::Vector2i mapDimensions = map.GetDimensions();

		if (mapDimensions.x <= Graphics::ScreenWidth)
		{
			newCameraCenter.x = mapDimensions.x / 2.0f;
		}
		else if (mode == Mode::Fixed)
		{
			newCameraCenter.x = playerPosition.x;
		}
		else if (mode == Mode::SemiFree)
		{
			const int cameraEdgeLeft = Graphics::ScreenWidth / 4;
			const int cameraEdgeRight = Graphics::ScreenWidth - cameraEdgeLeft;

			const sf::Vector2f& windowCenter = windowView.getCenter();

			if (playerScreenPosition.x < cameraEdgeLeft)
			{
				newCameraCenter.x -= cameraEdgeLeft - playerScreenPosition.x;
			}
			else if (playerScreenPosition.x > cameraEdgeRight)
			{
				newCameraCenter.x += playerScreenPosition.x - cameraEdgeRight;
			}
		}

		if (mapDimensions.y <= Graphics::ScreenHeight)
		{
			newCameraCenter.y = mapDimensions.y / 2.0f;
		}
		else if (mode == Mode::Fixed)
		{
			newCameraCenter.y = playerPosition.y;
		}
		else if (mode == Mode::SemiFree)
		{
			const int cameraEdgeTop = Graphics::ScreenHeight / 4;
			const int cameraEdgeBottom = Graphics::ScreenHeight - cameraEdgeTop;

			if (playerScreenPosition.y < cameraEdgeTop)
			{
				newCameraCenter.y -= cameraEdgeTop - playerScreenPosition.y;
			}
			else if (playerScreenPosition.y > cameraEdgeBottom)
			{
				newCameraCenter.y += playerScreenPosition.y - cameraEdgeBottom;
			}
		}

		constexpr int halfWindowWidth = Graphics::ScreenWidth / 2;
		constexpr int halfWindowHeight = Graphics::ScreenHeight / 2;

		if (newCameraCenter.x < halfWindowWidth)
		{
			newCameraCenter.x = static_cast<float>(halfWindowWidth);
		}
		else
		{
			const int cameraEdgeRight = mapDimensions.x - halfWindowWidth;

			if (newCameraCenter.x > cameraEdgeRight)
			{
				newCameraCenter.x = static_cast<float>(cameraEdgeRight);
			}
		}

		if (newCameraCenter.y < halfWindowHeight)
		{
			newCameraCenter.y = static_cast<float>(halfWindowHeight);
		}
		else
		{
			const int cameraEdgeBottom = mapDimensions.y - halfWindowHeight;

			if (newCameraCenter.y > cameraEdgeBottom)
			{
				newCameraCenter.y = static_cast<float>(cameraEdgeBottom);
			}
		}

		windowView.setCenter(newCameraCenter);

		previousCameraCenter = newCameraCenter;
	}

	window.setView(windowView);

	previousPlayerPosition = playerPosition;
	previousPlayerDimensions = playerDimensions;
}

void Camera::SwitchMode(const Mode mode)
{
	this->mode = mode;
	UpdatePlayerPosition(previousPlayerPosition, previousPlayerDimensions);
}