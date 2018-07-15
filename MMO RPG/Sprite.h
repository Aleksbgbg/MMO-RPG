#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <memory>

class Sprite : public sf::Sprite
{
public:
	Sprite() = default;
	explicit Sprite(const std::shared_ptr<sf::Texture>& texture);
	Sprite(const std::shared_ptr<sf::Texture>& texture, const sf::IntRect& rectangle);

private:
	std::shared_ptr<sf::Texture> texture;
};