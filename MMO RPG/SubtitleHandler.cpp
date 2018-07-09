#include "SubtitleHandler.h"

#include "RegularSubtitleText.h"
#include "FlashingText.h"

void SubtitleHandler::Emplace(const SubtitleType type, const std::string& text)
{
	const auto activeSubtitle = activeSubtitles.find(type);

	if (activeSubtitle == activeSubtitles.end())
	{
		activeSubtitles.emplace(type, MakeSubtitle(type, text));
	}
	else
	{
		if (activeSubtitle->second->GetText() == text)
		{
			return;
		}

		activeSubtitle->second = MakeSubtitle(type, text);
	}
}

void SubtitleHandler::Emplace(const SubtitleType type, const std::string& text, const float timeout)
{
	const auto activeTimeout = subtitleTimeouts.find(type);

	if (activeTimeout == subtitleTimeouts.end())
	{
		Emplace(type, text);

		subtitleTimeouts.emplace(type, timeout);
	}
	else
	{
		activeTimeout->second.Reset(timeout);
	}
}

void SubtitleHandler::Remove(const SubtitleType type)
{
	const auto iterator = activeSubtitles.find(type);

	if (iterator != activeSubtitles.end())
	{
		activeSubtitles.erase(iterator);
	}
}

void SubtitleHandler::Update()
{
	for (auto iterator = subtitleTimeouts.begin(); iterator != subtitleTimeouts.end(); )
	{
		auto& subtitleTimeout = *iterator;

		subtitleTimeout.second.Update();

		if (subtitleTimeout.second.TimedOut())
		{
			activeSubtitles.erase(activeSubtitles.find(subtitleTimeout.first));

			iterator = subtitleTimeouts.erase(iterator);
			continue;
		}

		++iterator;
	}

	for (const auto& activeSubtitle : activeSubtitles)
	{
		activeSubtitle.second->Update();
	}
}

void SubtitleHandler::Draw(const Graphics& gfx) const
{
	int verticalOffset = BetwixtTextOffset;

	for (const auto& activeSubtitle : activeSubtitles)
	{
		activeSubtitle.second->Draw(gfx, gfx.MapPixelToCoords(sf::Vector2i{ Graphics::ScreenWidth / 2, Graphics::ScreenHeight - verticalOffset }));

		verticalOffset += activeSubtitle.second->GetDimensions().height + BetwixtTextOffset;
	}
}

std::unique_ptr<Subtitle> SubtitleHandler::MakeSubtitle(const SubtitleType type, const std::string& text)
{
	switch (type)
	{
	case SubtitleType::Dialogue:
	case SubtitleType::Warning:
		return std::make_unique<RegularSubtitleText>(text);

	case SubtitleType::Action:
		return std::make_unique<FlashingText>(text);

	default:
		throw std::runtime_error{ "Invalid subtitle type." };
	}
}