#pragma once

#include <map>
#include <unordered_map>
#include <memory>

#include "Subtitle.h"
#include "TimeoutTracker.h"

class SubtitleHandler
{
public:
	enum class SubtitleType
	{
		Dialogue,
		Action,
		Warning
	};

public:
	void Emplace(const SubtitleType type, const std::string& text);
	void Emplace(const SubtitleType type, const std::string& text, const float timeout);

	void Remove(const SubtitleType type);

	void Update();
	void Draw(const Graphics& gfx) const;

private:
	static std::unique_ptr<Subtitle> MakeSubtitle(const SubtitleType type, const std::string& text);

private:
	static constexpr int BetwixtTextOffset = 5;

private:
	std::unordered_map<SubtitleType, TimeoutTracker> subtitleTimeouts;
	std::map<SubtitleType, std::unique_ptr<Subtitle>> activeSubtitles;
};