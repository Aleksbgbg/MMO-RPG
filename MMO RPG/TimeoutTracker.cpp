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

bool TimeoutTracker::TimedOut() const
{
	return runningTime >= timeout;
}