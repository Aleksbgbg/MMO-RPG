#include "Random.h"

int Random::Generate(const int start, const int end)
{
	return random.Next(start, end);
}

float Random::GenerateFloat(const float start, const float end)
{
	return random.NextFloat(start, end);
}

Random::Random()
	:
	Random{ std::random_device{ }() }
{
}

Random::Random(const int seed)
	:
	randomEngine{ seed }
{
}

int Random::Next(const int start, const int end)
{
	return std::uniform_int_distribution<int>{ start, end }(randomEngine);
}

float Random::NextFloat(const float start, const float end)
{
	return std::uniform_real_distribution<float>{ start, end }(randomEngine);
}