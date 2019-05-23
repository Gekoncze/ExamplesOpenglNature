#pragma once
#include <string>
#include <vector>

#define FACE_VERTEX_COUNT 3
#define VERTEX_COORD_COUNT 3
#define UV_COORD_COUNT 2

typedef struct Vertex {
	float x;
	float y;
	float z;
} Vertex;

typedef struct Uv {
	float x;
	float y;
} Uv;

typedef struct Ids {
	int v;
	int u;
} Ids;

typedef struct Face {
	Ids id[FACE_VERTEX_COUNT];
} Face;

typedef std::vector<Vertex> Vertices;
typedef std::vector<Uv> Uvs;
typedef std::vector<Face> Faces;

class ModelReader
{
private:
	float* vertex = nullptr;
	float* uv = nullptr;
	int vertexCount;

public:
	ModelReader(std::string path);
	~ModelReader();

	float* getVertices()
	{
		return vertex;
	}

	float* getUvs()
	{
		return uv;
	}

	int getVertexCount()
	{
		return vertexCount;
	}

private:
	void generateArrays(Vertices& v, Uvs& u, Faces& f);
};

