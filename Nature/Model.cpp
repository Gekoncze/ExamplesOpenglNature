#include "Model.h"
#include <exception>
#include "IOException.h"
#include "ImageReader.h"
#include "FileReader.h"
#include "ModelReader.h"
#include "Logger.h"

using namespace cz_mg_opengl;

Model::Model(std::string folder, std::string texturePath, std::string modelPath, std::string vsPath, std::string fsPath)
{
	texture = nullptr;
	vertexBuffer = nullptr;
	uvBuffer = nullptr;
	program = nullptr;
	vertexCount = 0;

	try
	{
		if (texturePath.size() > 0)
		{
			ImageReader imageReader(folder + "/" + texturePath);
			texture = new Texture(imageReader.getWidth(), imageReader.getHeight(), imageReader.getData(), true);
		}

		if (modelPath.size() > 0)
		{
			ModelReader modelReader(folder + "/" + modelPath);
			vertexBuffer = new FloatBuffer(modelReader.getVertices(), VERTEX_COORD_COUNT, modelReader.getVertexCount() * VERTEX_COORD_COUNT);
			uvBuffer = new FloatBuffer(modelReader.getUvs(), UV_COORD_COUNT, modelReader.getVertexCount() * UV_COORD_COUNT);
			vertexCount = modelReader.getVertexCount();
		}

		if (vsPath.size() > 0 && fsPath.size() > 0)
		{
			program = new Program(
				FileReader::readAll(folder + "/" + vsPath),
				FileReader::readAll(folder + "/" + fsPath)
			);
		}

		if (vertexBuffer != nullptr && uvBuffer != nullptr)
		{
			vertexArray.bind();
			vertexArray.setAttribute(0, *vertexBuffer);
			vertexArray.setAttribute(1, *uvBuffer);
		}
	}
	catch (std::exception& e)
	{
		if (texture != nullptr) delete texture;
		if (vertexBuffer != nullptr) delete vertexBuffer;
		if (uvBuffer != nullptr) delete uvBuffer;
		if (program != nullptr) delete program;
		throw e;
	}
	catch (...)
	{
		if (texture != nullptr) delete texture;
		if (vertexBuffer != nullptr) delete vertexBuffer;
		if (uvBuffer != nullptr) delete uvBuffer;
		if (program != nullptr) delete program;
		throw IOException("Could not load model.");
	}
}

Model::~Model()
{
	if (texture != nullptr) delete texture;
	if (vertexBuffer != nullptr) delete vertexBuffer;
	if (uvBuffer != nullptr) delete uvBuffer;
	if (program != nullptr) delete program;
}
