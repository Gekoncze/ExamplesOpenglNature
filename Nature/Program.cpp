#include "Program.h"
#include "Logger.h"
#include "StringUtilities.h"

#define BUFFER_SIZE 4000

using namespace cz_mg_opengl;
using namespace cz_mg_logger;

Program::Program(std::string vertexShaderCode, std::string fragmentShaderCode)
{
	VertexShaderHandle vertexShader;
	FragmentShaderHandle fragmentShader;
	compileShader(vertexShader, vertexShaderCode);
	compileShader(fragmentShader, fragmentShaderCode);
	linkProgram(program, vertexShader, fragmentShader);
}

Program::~Program()
{
}

void Program::use()
{
	//Opengl::checkError("Uncaught error!");
	//glValidateProgram(program.getHandle());
	//Opengl::checkError("Could not validate program!");
	//GLint result;
	//glGetProgramiv(program.getHandle(), GL_VALIDATE_STATUS, &result);
	//if (result != GL_TRUE)
	//{
	//	GLsizei length;
	//	GLchar infoLog[4000];
	//	glGetProgramInfoLog(program.getHandle(), 4000, &length, infoLog);
	//	Opengl::checkError("Could not get info log!");
	//	throw OpenglException(std::string("Validation was not successful: ") + infoLog + " XXX " + length + " ### given handle " + program.getHandle());
	//}
	glUseProgram(program.getHandle());
	Opengl::checkError("Could not use program. !!!");
}

int Program::getAttributeLocation(std::string name)
{
	int rval = glGetAttribLocation(program.getHandle(), name.c_str());
	Opengl::checkError("Could not get attribute " + name + " handle.");
	return rval;
}

int Program::getUniformLocation(std::string name)
{
	int rval = glGetUniformLocation(program.getHandle(), name.c_str());
	Opengl::checkError("Could not get uniform handle " + name + ".");
	return rval;
}

void Program::setTexture(std::string name, Texture& texture)
{
	int handle = getUniformLocation(name);
	if (handle < 0) return;
	glActiveTexture(GL_TEXTURE0 + nextTextureId);
	Opengl::checkError("Could not activate texture " + name + " (" + nextTextureId + ").");
	glBindTexture(GL_TEXTURE_2D, texture.getTexture().getHandle());
	Opengl::checkError("Could not bind texture " + name + ".");
	glUniform1i(handle, nextTextureId);
	Opengl::checkError("Could not set texture " + name + ".");

	nextTextureId++;
}

void Program::setMatrix(std::string name, Matrix4f& matrix)
{
	int handle = getUniformLocation(name);
	glUniformMatrix4fv(handle, 1, false, matrix.getData());
	Opengl::checkError("Could not set matrix " + name + ".");
}

void Program::setUniform1f(std::string name, float value)
{
	int handle = getUniformLocation(name);
	glUniform1f(handle, value);
	Opengl::checkError("Could not set " + name + " (1f).");
}

void Program::setUniform2f(std::string name, float x, float y)
{
	int handle = getUniformLocation(name);
	glUniform2f(handle, x, y);
	Opengl::checkError("Could not set " + name + " (2f).");
}

void Program::setUniform3f(std::string name, float x, float y, float z)
{
	int handle = getUniformLocation(name);
	glUniform3f(handle, x, y, z);
	Opengl::checkError("Could not set " + name + " (3f).");
}

void Program::setUniform4f(std::string name, float x, float y, float z, float w)
{
	int handle = getUniformLocation(name);
	glUniform4f(handle, x, y, z, w);
	Opengl::checkError("Could not set " + name + " (4f).");
}

void Program::draw(int shape, int count)
{
	glDrawArrays(shape, 0, count);
	Opengl::checkError("Could not draw arrays.");
}

void Program::drawInstances(int shape, int count, int instanceCount)
{
	glDrawArraysInstanced(shape, 0, count, instanceCount);
	Opengl::checkError("Could not draw array instances.");
}

void Program::resetValues() {
	nextTextureId = 0;	
}

void Program::compileShader(Handle& shader, std::string code)
{
	const char* c = code.c_str();
	GLint s = code.size();
	glShaderSource(shader.getHandle(), 1, &c, &s);
	glCompileShader(shader.getHandle());
	Opengl::checkError("Could not compile shader.");
	checkShader(shader);
}

void Program::checkShader(Handle& shader)
{
	GLint result;
	glGetShaderiv(shader.getHandle(), GL_COMPILE_STATUS, &result);
	Opengl::checkError("Could not get compile status.");
	if (result == GL_FALSE)
	{
		char message[BUFFER_SIZE];
		int length = -1;
		glGetShaderInfoLog(shader.getHandle(), BUFFER_SIZE, &length, message);
		Logger::log("Shader didnt compile: " + std::string(message) + " ((" + length + "))");
		throw OpenglException(message);
	}
}

void Program::linkProgram(ProgramHandle& program, VertexShaderHandle& vertexShader, FragmentShaderHandle& fragmentShader)
{
	glAttachShader(program.getHandle(), vertexShader.getHandle());
	glAttachShader(program.getHandle(), fragmentShader.getHandle());
	glLinkProgram(program.getHandle());
	Opengl::checkError("Could not link program.");
	checkProgram(program);
}

void Program::checkProgram(ProgramHandle& program)
{
	GLint result;
	glGetProgramiv(program.getHandle(), GL_LINK_STATUS, &result);
	Opengl::checkError("Could not get link status.");
	if (result == GL_FALSE) {
		char message[BUFFER_SIZE];
		int length;
		glGetProgramInfoLog(program.getHandle(), BUFFER_SIZE, &length, message);
		throw OpenglException(message);
	}
}
