#pragma once

class TimeoutTracker
{
public:
	explicit TimeoutTracker(const float timeout);

public:
	void Update();

	bool TimedOut() const;

private:
	const float timeout;

	float runningTime;
};