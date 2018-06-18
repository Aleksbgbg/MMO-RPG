#include "Animation.h"

#include "DeltaTime.h"

Animation::Animation(sf::Sprite& sprite, const SpriteInfo& spriteInfo, const int sheetRow)
	:
	_sprite{ sprite },
	_frameSize{ spriteInfo.frameRegion.x / spriteInfo.frameCount, spriteInfo.frameRegion.y },
	_startingPosition{ 0, sheetRow * spriteInfo.spriteDimension.y },
	_frameTime{ spriteInfo.frameTime },
	_currentFrameRunningTime{ 0.0f },
	_frameCount{ spriteInfo.frameCount },
	_defaultFrame{ spriteInfo.standingFrameIndex },
	_currentFrame{ 0 },
	_isStopped{ false }
{
	SwitchFrame(_defaultFrame);
}

void Animation::SwitchFrame(const int frame) const
{
	_sprite.setTextureRect(sf::IntRect{ _startingPosition.x + _frameSize.x * frame, _startingPosition.y, _frameSize.x, _frameSize.y });
}

void Animation::Resume()
{
	_isStopped = false;
}

void Animation::Stop()
{
	SwitchFrame(_defaultFrame);
	_isStopped = true;
}

void Animation::Update()
{
	_currentFrameRunningTime += DeltaTime::Get();

	while (_currentFrameRunningTime > _frameTime)
	{
		NextFrame();
		_currentFrameRunningTime -= _frameTime;
	}

	SwitchFrame(_currentFrame);
}

void Animation::NextFrame()
{
	++_currentFrame;

	if (_currentFrame >= _frameCount)
	{
		_currentFrame = 0;
	}
}