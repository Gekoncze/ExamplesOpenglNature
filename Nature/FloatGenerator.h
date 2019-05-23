#pragma once
class FloatGenerator
{
public:
	FloatGenerator();
	FloatGenerator(int seed);
	~FloatGenerator();

	float nextFloat();
	float next(float min, float max);
	float nextFaveMax(float min, float max);
	float nextFaveMin(float min, float max);

private:
	float resize(float value, float min, float max);
};

