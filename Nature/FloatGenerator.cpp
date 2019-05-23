#include "FloatGenerator.h"
#include <cstdlib>
#include <ctime>

FloatGenerator::FloatGenerator()
{
	srand(time(NULL));
}

FloatGenerator::FloatGenerator(int seed)
{
	srand(seed);
}

FloatGenerator::~FloatGenerator()
{
}

float FloatGenerator::nextFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

float FloatGenerator::next(float min, float max)
{
	return resize(nextFloat(), min, max);
}

float FloatGenerator::nextFaveMax(float min, float max)
{
	float f = (nextFloat() - 1.0f);
	return resize(1.0f - f * f * f * f, min, max);
}

float FloatGenerator::nextFaveMin(float min, float max)
{
	float f = ((1.0f - nextFloat()) - 1.0f);
	return resize(1.0f - f * f * f * f, min, max);
}

float FloatGenerator::resize(float value, float min, float max)
{
	return min + value * (max - min);
}
