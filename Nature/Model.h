#pragma once
#include <string>
#include "Texture.h"
#include "FloatBuffer.h"
#include "Program.h"
#include "Opengl.h"
#include "VertexArray.h"

namespace gl = cz_mg_opengl;

class Model
{
	NOCOPY(Model)

	gl::Texture* texture;
    gl::FloatBuffer* vertexBuffer;
    gl::FloatBuffer* uvBuffer;
    gl::Program* program;
	int vertexCount;
    gl::VertexArray vertexArray;

public:
	Model(std::string folder, std::string texturePath, std::string modelPath, std::string vsPath, std::string fsPath);
	~Model();

    gl::Texture& getTexture()
	{
		return *texture;
	}

    gl::FloatBuffer& getVertexBuffer()
	{
		return *vertexBuffer;
	}

    gl::FloatBuffer& getUvBuffer()
	{
		return *uvBuffer;
	}

    gl::Program& getProgram()
	{
		return *program;
	}

	int getVertexCount()
	{
		return vertexCount;
	}

    gl::VertexArray& getVertexArray()
	{
		return vertexArray;
	}
};
