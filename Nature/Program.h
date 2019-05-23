#pragma once
#include "ProgramHandle.h"
#include "VertexShaderHandle.h"
#include "FragmentShaderHandle.h"
#include "OpenglException.h"
#include "Opengl.h"
#include "Matrix4f.h"
#include "FloatBuffer.h"
#include "StringUtilities.h"
#include "Texture.h"
#include <vector>
#include <string>

namespace cz_mg_opengl
{
    class Program
    {
        NOCOPY(Program)

    private:
        ProgramHandle program;
        int nextTextureId = 0;

    public:
        Program(std::string vertexShaderCode, std::string fragmentShaderCode);
        ~Program();

    public:
        void use();
        int getAttributeLocation(std::string name);
        int getUniformLocation(std::string name);
        void setTexture(std::string name, Texture& texture);
        void setMatrix(std::string name, Matrix4f& matrix);
        void setUniform1f(std::string name, float value);
        void setUniform2f(std::string name, float x, float y);
        void setUniform3f(std::string name, float x, float y, float z);
        void setUniform4f(std::string name, float x, float y, float z, float w);
        void draw(int shape, int count);
        void drawInstances(int shape, int count, int instanceCount);
        void resetValues();

    private:
        void compileShader(Handle& shader, std::string code);
        void checkShader(Handle& shader);
        void linkProgram(ProgramHandle& program, VertexShaderHandle& vertexShader, FragmentShaderHandle& fragmentShader);
        void checkProgram(ProgramHandle& program);
    };
}
