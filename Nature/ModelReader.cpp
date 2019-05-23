#include "ModelReader.h"
#include "FileReader.h"
#include "IOException.h"
#include "StringUtilities.h"
#include "StringTokenizer.h"
#include "Logger.h"

static void parseLine(std::string line, Vertices& v, Uvs& u, Faces& f);
static void parseVertex(StringTokenizer& tk, Vertices& v);
static void parseUv(StringTokenizer& tk, Uvs& u);
static void parseFace(StringTokenizer& tk, Faces& f);

ModelReader::ModelReader(std::string path)
{
	vertexCount = 0;

	Vertices v;
	Uvs u;
	Faces f;

	FileReader reader(path);
	std::string line;
	int lineNumber = 1;

	try {
		while (reader.readLine(line)) {
			parseLine(line, v, u, f);
			lineNumber++;
		}
	} catch (std::exception e) {
		throw IOException(std::string("Could not parse line ") + lineNumber + std::string(" '") + line + std::string("'"));
	}

	generateArrays(v, u, f);
}

ModelReader::~ModelReader()
{
	if (vertex != nullptr) delete[] vertex;
	if (uv != nullptr) delete[] uv;
}

static void parseLine(std::string line, Vertices& v, Uvs& u, Faces& f)
{
	if (line.length() < 1) return;

	StringTokenizer tk(line, " /");
	std::string type = tk.nextToken();

	if(type == "v3") parseVertex(tk, v);
	if(type == "t3") parseUv(tk, u);
	if(type == "f3") parseFace(tk, f);
}

static void parseVertex(StringTokenizer& tk, Vertices& v)
{
	Vertex vertex;
	vertex.x = std::stof(tk.nextToken());
	vertex.y = std::stof(tk.nextToken());
	vertex.z = std::stof(tk.nextToken());
	v.push_back(vertex);
}

static void parseUv(StringTokenizer& tk, Uvs& u)
{
	Uv uv;
	uv.x = std::stof(tk.nextToken());
	uv.y = std::stof(tk.nextToken());
	u.push_back(uv);
}

static void parseFace(StringTokenizer& tk, Faces& f)
{
	Face face;
	for (int i = 0; i < FACE_VERTEX_COUNT; i++) {
		face.id[i].v = std::stoi(tk.nextToken());
		face.id[i].u = std::stoi(tk.nextToken());
		tk.nextToken(); // unused color token
	}
	f.push_back(face);
}

void ModelReader::generateArrays(Vertices& v, Uvs& u, Faces& f)
{
	vertex = new float[f.size() * VERTEX_COORD_COUNT * FACE_VERTEX_COUNT];
	uv = new float[f.size() * UV_COORD_COUNT * FACE_VERTEX_COUNT];

	int cv = 0;
	int cu = 0;
	for (int i = 0; i < f.size(); i++) {
		Face ff = f[i];
		for (int j = 0; j < FACE_VERTEX_COUNT; j++) {
			Vertex& vv = v[ff.id[j].v];
			Uv& uu = u[ff.id[j].u];
			vertex[cv] = vv.x; cv++;
			vertex[cv] = vv.y; cv++;
			vertex[cv] = vv.z; cv++;
			uv[cu] = uu.x; cu++;
			uv[cu] = uu.y; cu++;
			vertexCount++;
		}
	}
}

