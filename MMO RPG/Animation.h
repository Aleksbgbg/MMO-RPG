#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <json.hpp>

#include "Direction.h"

class Animation
{
public:
	Animation(sf::Sprite& sprite, const nlohmann::json& animationInfo, const Direction animationDirection);

public:
	void SwitchFrame(const int frame) const;

	void Resume();
	void Stop();	

	void Update();

private:
	void NextFrame();

private:
	sf::Sprite& sprite;

	const sf::Vector2i frameSize;
	const int rowOffset;

	const float frameTime;
	float currentFrameRunningTime;

	const int frameCount;
	const int defaultFrame;
	int currentFrame;

	bool isStopped;
};