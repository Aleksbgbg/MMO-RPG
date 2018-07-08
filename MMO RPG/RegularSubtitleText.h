#pragma once

#include "Subtitle.h"

class RegularSubtitleText : public Subtitle
{
public:
	explicit RegularSubtitleText(const std::string& string);

private:
	sf::Text text;
};