#include "Animation.h"

#include "DeltaTime.h"

Animation::Animation(sf::Sprite& sprite, const SpriteInfo& spriteInfo, const int sheetRow, const sf::IntRect spriteRegion)
	:
	sprite{ sprite },
	frameSize{ spriteInfo.frameRegion.x / spriteInfo.frameCount, spriteInfo.frameRegion.y },
	startingPosition{ spriteRegion.left, spriteRegion.top + sheetRow * spriteInfo.spriteDimension.y },
	frameTime{ spriteInfo.frameTime },
	currentFrameRunningTime{ 0.0f },
	frameCount{ spriteInfo.frameCount },
	defaultFrame{ spriteInfo.standingFrameIndex },
	currentFrame{ 0 },
	isStopped{ false }
{
	SwitchFrame(defaultFrame);
}

void Animation::SwitchFrame(const int frame) const
{
	sprite.setTextureRect(sf::IntRect{ startingPosition.x + frameSize.x * frame, startingPosition.y, frameSize.x, frameSize.y });
}

void Animation::Resume()
{
	isStopped = false;
}

void Animation::Stop()
{
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