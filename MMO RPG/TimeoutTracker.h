#pragma once

class TimeoutTracker
{
public:
	explicit TimeoutTracker(const float timeout);

public:
	void Update();

	void Reset();
	void Reset(const float newTimeout);

	bool TimedOut() const;

private:
	float timeout;

	float runningTime;
};