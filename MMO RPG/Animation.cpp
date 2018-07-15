#include "Animation.h"

#include "DeltaTime.h"

Animation::Animation(Sprite& sprite, const nlohmann::json& animationInfo, const Direction animationDirection)
	:
	sprite{ sprite },
	frameSize{ animationInfo["width"], animationInfo["height"] },
	rowOffset{ static_cast<int>(animationInfo["animationRows"][std::to_string(static_cast<int>(animationDirection))]) * frameSize.y },
	frameTime{ animationInfo["frameTime"] },
	currentFrameRunningTime{ 0.0f },
	frameCount{ animationInfo["frameCount"] },
	defaultFrame{ animationInfo["defaultFrame"] },
	currentFrame{ 0 },
	isStopped{ false }
{
	SwitchFrame(defaultFrame);
}

void Animation::SwitchFrame(const int frame) const
{
	sprite.setTextureRect(sf::IntRect{ frameSize.x * frame, rowOffset, frameSize.x, frameSize.y });
}

void Animation::Resume()
{
	isStopped = false;
}

void Animation::Stop()
{
	currentFrameRunningTime = 0;

	SwitchFrame(defaultFrame);

	isStopped = true;
}

void Animation::Update()
{
	currentFrameRunningTime += DeltaTime::Get();

	while (currentFrameRunningTime > frameTime)
	{
		NextFrame();
		currentFrameRunningTime -= frameTime;
	}

	if (currentFrame == defaultFrame)
	{
		NextFrame();
	}

	SwitchFrame(currentFrame);
}

void Animation::NextFrame()
{
	++currentFrame;

	if (currentFrame >= frameCount)
	{
		currentFrame = 0;
	}
}