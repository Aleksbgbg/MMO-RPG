#include "RegularSubtitleText.h"

#include "ResourceManager.h"

RegularSubtitleText::RegularSubtitleText(const std::string& string)
	:
	Subtitle{ text },
	text{ string, FontManager::Get("arial") }
{
	Setup();
}