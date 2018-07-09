#include "TimeoutTracker.h"

#include "DeltaTime.h"

TimeoutTracker::TimeoutTracker(const float timeout)
	:
	timeout{ timeout },
	runningTime{ 0.0f }
{
}

void TimeoutTracker::Update()
{
	runningTime += DeltaTime::Get();
}

void TimeoutTracker::Reset()
{
	runningTime = 0.0f;
}

void TimeoutTracker::Reset(const float newTimeout)
{
	Reset();
	timeout = newTimeout;
}

bool TimeoutTracker::TimedOut() const
{
	return runningTime >= timeout;
}