#pragma once
#include "GrassClump.h"
#include <vector>
#include "FloatGenerator.h"
#include "ModelReader.h"

#define MIN_SIZE 10.0f
#define MAX_SIZE 20.0f
#define COLOR Color3f(0.5f, 1.0f, 0.0f)
#define COLOR_DRY Color3f(1.0f, 1.0f, 0.0f)
#define MIN_PLIABILITY 0.2f
#define MAX_PLIABILITY 1.0f

class GrassGenerator
{
public:
	GrassGenerator();
	~GrassGenerator();

	static void generate(ModelReader& terrain, float scale, int count, int seed, float xmin, float ymin, float xmax, float ymax, std::vector<GrassClump>& clumps);

private:
	static float getModelZ(ModelReader& terrain, float x, float y);
	static float getPlaneZ(float x, float y, Vector3f p1, Vector3f p2, Vector3f p3);
	static bool pointInTriangle(Vector3f p, Vector3f v1, Vector3f v2, Vector3f v3);
	static float sign(Vector3f p1, Vector3f p2, Vector3f p3);
};

