#include "GrassGenerator.h"

GrassGenerator::GrassGenerator()
{
}

GrassGenerator::~GrassGenerator()
{
}

void GrassGenerator::generate(ModelReader& terrain, float scale, int count, int seed, float xmin, float ymin, float xmax, float ymax, std::vector<GrassClump>& clumps)
{
	clumps.resize(count);
	FloatGenerator generator(seed);
	for (int i = 0; i < count; i++) {
		float x = generator.next(xmin, xmax);
		float y = generator.next(ymin, ymax);
		Vector3f position(scale * x, scale * y, scale * getModelZ(terrain, x, y));
		float size = generator.nextFaveMax(MIN_SIZE, MAX_SIZE);
		float colorOffset = generator.nextFloat();//1 - (float)OpenSimplexNoise.noiseExt(x, y, 1, 0, 1, 100);
		Color3f color = Color3f::mix(COLOR, COLOR_DRY, colorOffset);
		float pliability = generator.next(MIN_PLIABILITY, MAX_PLIABILITY);

		clumps[i] = GrassClump(position, color, size, pliability);
	}
}

float GrassGenerator::getModelZ(ModelReader& terrain, float x, float y)
{
	int arrayLength = terrain.getVertexCount() * 3;

	float* array = terrain.getVertices();
	Vector3f p1(0, 0, 0);
	Vector3f p2(0, 0, 0);
	Vector3f p3(0, 0, 0);
	Vector3f p(x, y, 0);

	for (int i = 0; i < arrayLength; i += 9) {
		p1.x = array[i + 0]; p1.y = array[i + 1]; p1.z = array[i + 2];
		p2.x = array[i + 3]; p2.y = array[i + 4]; p2.z = array[i + 5];
		p3.x = array[i + 6]; p3.y = array[i + 7]; p3.z = array[i + 8];

		if (pointInTriangle(p, p1, p2, p3)) {
			return getPlaneZ(x, y, p1, p2, p3);
		}
	}

	return 0;
}

float GrassGenerator::getPlaneZ(float x, float y, Vector3f p1, Vector3f p2, Vector3f p3)
{
	Vector3f v1 = Vector3f::minus(p1, p2);
	Vector3f v2 = Vector3f::minus(p1, p3);
	Vector3f n = Vector3f::cross(v1, v2);
	// nx * x + ny * y + nz * z + d = 0
	// d = -(nx*x + ny*y + nz*z)
	// z = -(nx*x + ny*y + d) / nz
	float d = -Vector3f::dotProduct(n, p1);
	return (n.x * x + n.y * y + d) / (-n.z);
}

bool GrassGenerator::pointInTriangle(Vector3f p, Vector3f v1, Vector3f v2, Vector3f v3)
{
	bool b1, b2, b3;

	b1 = sign(p, v1, v2) < 0.0f;
	b2 = sign(p, v2, v3) < 0.0f;
	b3 = sign(p, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

float GrassGenerator::sign(Vector3f p1, Vector3f p2, Vector3f p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}
