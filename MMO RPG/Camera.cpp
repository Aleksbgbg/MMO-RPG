#include "Camera.h"
#include "Graphics.h"
#include "Vector.h"

Camera::Camera(sf::RenderWindow& window, const Map& map)
	:
	window{ window },
	map{ map },
	mode{ Mode::Fixed }
{
}

void Camera::UpdatePosition(const sf::Vector2f playerPosition)
{
	sf::View windowView{ window.getView() };

	{
		sf::Vector2f newCameraCenter{ previousCameraCenter };

		const sf::Vector2i playerScreenPosition = window.mapCoordsToPixel(playerPosition);

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
			const int cameraEdgeLeft = static_cast<int>(Graphics::ScreenWidth / (1 / SemiFreeCameraEdgePercentage));
			const int cameraEdgeRight = Graphics::ScreenWidth - cameraEdgeLeft;

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
			const int cameraEdgeTop = static_cast<int>(Graphics::ScreenHeight / (1 / SemiFreeCameraEdgePercentage));
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
}

void Camera::SwitchMode(const Mode mode)
{
	this->mode = mode;
	UpdatePosition(previousPlayerPosition);
}

void Camera::MoveBy(sf::Vector2f movement)
{
	if (mode != Mode::SemiFree) return;

	normalize(movement);

	movement.x *= CameraMovementMultiplier;
	movement.y *= CameraMovementMultiplier;

	previousCameraCenter += movement;

	UpdatePosition(previousPlayerPosition);
}

Camera::Mode Camera::GetMode() const
{
	return mode;
}

sf::FloatRect Camera::GetViewArea() const
{
	const sf::Vector2f screenDimensions{ static_cast<float>(Graphics::ScreenWidth), static_cast<float>(Graphics::ScreenHeight) };

	sf::Vector2f cameraEdge{ previousCameraCenter };

	cameraEdge.x -= screenDimensions.x / 2;
	cameraEdge.y -= screenDimensions.y / 2;

	return sf::FloatRect{ cameraEdge, screenDimensions };
}