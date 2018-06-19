#pragma once

#include <random>

// Generates in the range [start, end]
class Random
{
public:
	static int Generate(const int start, const int end);
	static float GenerateFloat(const float start, const float end);

private:
	inline static Random random;

public:
	Random();
	explicit Random(const int seed);

public:
	int Next(const int start, const int end);
	float NextFloat(const float start, const float end);

private:
	std::mt19937 randomEngine;
};