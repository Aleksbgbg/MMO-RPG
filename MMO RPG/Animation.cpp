#include "Animation.h"

#include "DeltaTime.h"

// Horizontal sprite sheet assumed
Animation::Animation(sf::Sprite& sprite, const sf::Vector2i frameRegion, const int frameCount, const sf::Vector2i startingPosition, const int defaultFrame, const float frameTime)
	:
	_sprite{ sprite },
	_frameSize{ frameRegion.x / frameCount, frameRegion.y },
	_startingPosition{ startingPosition },
	_frameTime{ frameTime },
	_currentFrameRunningTime{ 0.0f },
	_frameCount{ frameCount },
	_defaultFrame{ defaultFrame },
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