#pragma once
#include "Renderer.h"
#include "Program.h"
#include "Camera.h"
#include "FloatBuffer.h"
#include "Texture.h"
#include "Matrix4f.h"
#include "Framebuffer.h"
#include "FileReader.h"
#include "Model.h"
#include "VertexArray.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "GrassClump.h"

#define PRECISION 48
#define BLEND_FACTOR 4

namespace gl = cz_mg_opengl;

class GraphicsRendererFrames {
public:
	gl::Framebuffer frame1;
    gl::Framebuffer frame2;

public:
	GraphicsRendererFrames(int width, int height) :
		frame1(width, height),
		frame2(width / BLEND_FACTOR, height / BLEND_FACTOR)
	{}
};

class GraphicsRendererModels {
public:
	Model grass;
	Model ground;
	Model frame1;
	Model frame2;

public:
	GraphicsRendererModels();
};

class GraphicsRendererGrassClumpBuffers {
public:
	gl::FloatBuffer colorBuffer;
	gl::FloatBuffer positionBuffer;
	gl::FloatBuffer pliabilityBuffer;

public:
	GraphicsRendererGrassClumpBuffers(std::vector<GrassClump> grassClumps);
};

class GraphicsRenderer : public Renderer
{
private:
	Camera camera;
	Matrix4f projection3D, projection2D;
	float wind_x = 0;
	float wind_y = 0;
	GraphicsRendererFrames* frames;
	GraphicsRendererModels* models;
	GraphicsRendererGrassClumpBuffers* clumpBuffers;
	std::vector<GrassClump> grassClumps;

public:
	GraphicsRenderer();
	~GraphicsRenderer();

	void addRotation(float yaw, float pitch);
	void addPosition(float x, float y);

	void onCreate();
	void onResize();

private:
	void updateProjection();

public:
	Camera& getCamera()
	{
		return camera;
	}

	void setWind(float x, float y);
	void onDraw();

private:
	void draw3D();
	void drawGround(Matrix4f& matrix);
	void drawGrass(Matrix4f& matrix);
	void draw2D();
	void drawFrame();
};
