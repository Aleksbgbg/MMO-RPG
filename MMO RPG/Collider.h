#pragma once

#include <SFML/Graphics/Rect.hpp>

bool are_overlapping(const sf::FloatRect& first, const sf::FloatRect& second);

bool is_inside(const sf::FloatRect& bounds, const sf::FloatRect& source);