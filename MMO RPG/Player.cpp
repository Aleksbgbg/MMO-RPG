#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "INIReader.h"

Player::Player(Graphics& gfx)
	:
	_sprite{ _spriteSheet },
	_movementDirection{ Direction::Down }
{
	if (!_spriteSheet.loadFromFile("Player.png"))
	{
		throw std::runtime_error{ "Player spritesheet loading not successful." };
	}

	gfx.Add(_sprite);

	INIReader iniReader{ "Player Sprite Config.ini" };

	const float animationTime = iniReader.GetReal("Sprite", "AnimationTime", 0);

	const sf::Vector2i spriteDimension{ iniReader.GetInteger("Sprite", "Width", 0), iniReader.GetInteger("Sprite", "Height", 0) };

	const int standingFrameIndex = iniReader.GetInteger("SpriteSheet", "StandingFrameIndex", 0);

	const int leftRow = iniReader.GetInteger("SpriteSheet", "LeftRow", 0);
	const int rightRow = iniReader.GetInteger("SpriteSheet", "RightRow", 0);
	const int upRow = iniReader.GetInteger("SpriteSheet", "UpRow", 0);
	const int downRow = iniReader.GetInteger("SpriteSheet", "DownRow", 0);

	const int frameCount = _spriteSheet.getSize().x / spriteDimension.x;

	const sf::Vector2i frameRegion{ static_cast<int>(_spriteSheet.getSize().x), spriteDimension.y };

	_animations.emplace(Direction::Up, Animation{ _sprite, frameRegion, frameCount, sf::Vector2i{ 0, upRow * spriteDimension.y }, standingFrameIndex, animationTime });
	_animations.emplace(Direction::Down, Animation{ _sprite, frameRegion, frameCount, sf::Vector2i{ 0, downRow * spriteDimension.y }, standingFrameIndex, animationTime });
	_animations.emplace(Direction::Left, Animation{ _sprite, frameRegion, frameCount, sf::Vector2i{ 0, leftRow * spriteDimension.y }, standingFrameIndex, animationTime });
	_animations.emplace(Direction::Right, Animation{ _sprite, frameRegion, frameCount, sf::Vector2i{ 0, rightRow * spriteDimension.y }, standingFrameIndex, animationTime });
}

void Player::Update()
{
	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		_movementDirection = Direction::Up;
		movement.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		_movementDirection = Direction::Down;
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		_movementDirection = Direction::Left;
		movement.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		_movementDirection = Direction::Right;
		movement.x = 1;
	}

	_sprite.move(movement);
	
	_animations.at(_movementDirection).Update();
}