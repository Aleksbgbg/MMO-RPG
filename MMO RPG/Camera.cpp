#include "Camera.h"

Camera::Camera(sf::RenderWindow& window)
	:
	window{ window }
{	
}

void Camera::UpdatePlayerPosition(sf::Vector2f playerPosition)
{
	sf::View windowView{ window.getView() };

	windowView.setCenter(playerPosition);

	window.setView(windowView);

	this->playerPosition = playerPosition;
}