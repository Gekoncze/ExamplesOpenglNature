#include "GraphicsRenderer.h"
#include "Logger.h"
#include "GrassGenerator.h"
#include "ModelReader.h"

using namespace cz_mg_opengl;
using namespace cz_mg_logger;

GraphicsRendererModels::GraphicsRendererModels() :
	grass("resources", "textures/grass.png", "models/grass", "shaders/vsGrass.glsl", "shaders/fsGrass.glsl"),
	ground("resources", "textures/ground.png", "models/ground", "shaders/vsGround.glsl", "shaders/fsGround.glsl"),
	frame1("resources", "", "models/frame", "shaders/vsFrame.glsl", "shaders/fsFrame.glsl"),
	frame2("resources", "", "models/frame", "shaders/vsFrame2.glsl", "shaders/fsFrame2.glsl")
{}

GraphicsRendererGrassClumpBuffers::GraphicsRendererGrassClumpBuffers(std::vector<GrassClump> grassClumps)
{
	int n = 3;
	int count = grassClumps.size() * n;

	std::vector<Color3f> colors;
	for (int i = 0; i < grassClumps.size(); i++) colors.push_back(grassClumps[i].color);

	std::vector<Vector3f> positions;
	for (int i = 0; i < grassClumps.size(); i++) positions.push_back(grassClumps[i].position);

	float* colorData = Color3f::createArray(colors);
	float* positionData = Vector3f::createArray(positions);
	float* pliabilityData = new float[grassClumps.size()];
	for (int i = 0; i < grassClumps.size(); i++) pliabilityData[i] = grassClumps[i].pliability;

	colorBuffer.setDataStatic(colorData, n, count);
	positionBuffer.setDataStatic(positionData, n, count);
	pliabilityBuffer.setDataStatic(pliabilityData, 1, count);

	delete[] colorData;
	delete[] positionData;
	delete[] pliabilityData;
}

GraphicsRenderer::GraphicsRenderer()
{
	frames = nullptr;
	models = nullptr;
	clumpBuffers = nullptr;
	Logger::log("Renderer constructor!");
}

GraphicsRenderer::~GraphicsRenderer()
{
	if (frames != nullptr) delete frames;
	if (models != nullptr) delete models;
	if (clumpBuffers != nullptr) delete clumpBuffers;
}

static void myDebugCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	Logger::log(std::string(message));
}

void GraphicsRenderer::onCreate()
{
	if (glewInit() != GLEW_OK) throw OpenglException("Could not init glew!");

	const GLubyte* version = glGetString(GL_VERSION);
	Opengl::checkError("Could not get current opengl version.");
	Logger::log(std::string("Using version ") + ((char*)version));

	glDebugMessageCallback(myDebugCallback, nullptr);

	try
	{
		Logger::log("Renderer onCreate!");
		camera.z = 50;
		camera.pitch = -45*3.1415/180;

		ModelReader terrain("resources/models/ground");
		GrassGenerator::generate(terrain, 100.0f, 750, 0, -1, -1, 1, 1, grassClumps);

		models = new GraphicsRendererModels();
		clumpBuffers = new GraphicsRendererGrassClumpBuffers(grassClumps);

		models->grass.getVertexArray().bind();
		models->grass.getVertexArray().setAttributeInstance(2, clumpBuffers->colorBuffer, 1);
		models->grass.getVertexArray().setAttributeInstance(3, clumpBuffers->positionBuffer, 1);
		models->grass.getVertexArray().setAttributeInstance(4, clumpBuffers->pliabilityBuffer, 1);
	}
	catch (OpenglException& e)
	{
		Logger::log(e.getMessage());
		throw e;
	}

	onResize();
}

void GraphicsRenderer::onResize()
{
	try {
		Logger::log("Renderer onResize!");
		updateProjection();
		glViewport(0, 0, getWidth(), getHeight());
		if (frames != nullptr) delete frames;
		frames = new GraphicsRendererFrames(getWidth(), getHeight());
	}
	catch (OpenglException& e)
	{
		Logger::log(e.getMessage());
		throw e;
	}
}

void GraphicsRenderer::updateProjection()
{
	projection3D = Matrix4f::perspective(45, getAspect(), 1.0f, 200.0f);
	projection2D = Matrix4f::ortho(0, getWidth(), 0, getHeight(), -1, 1);
}

void GraphicsRenderer::addRotation(float yaw, float pitch)
{
	camera.yaw += yaw;
	camera.pitch += pitch;
}

void GraphicsRenderer::addPosition(float x, float y)
{
	camera.x += cos(camera.yaw) * x;
	camera.y -= sin(camera.yaw) * x;
	camera.x += sin(camera.yaw) * y;
	camera.y += cos(camera.yaw) * y;
}

void GraphicsRenderer::setWind(float x, float y)
{
	wind_x = x;
	wind_y = y;
}

void GraphicsRenderer::onDraw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw3D();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_DEPTH_BUFFER_BIT);
	draw2D();
}

void GraphicsRenderer::draw3D()
{
	try
	{
		frames->frame1.use();
		Matrix4f matrix = Matrix4f::multiply(projection3D, camera.getMatrix());
		drawGround(matrix);
		drawGrass(matrix);
		frames->frame1.unuse();
	}
	catch (OpenglException& e)
	{
		Logger::log(e.getMessage());
		throw e;
	}
}

void GraphicsRenderer::drawGround(Matrix4f& matrix)
{
	try
	{
		Matrix4f groundMatrix = Matrix4f::multiply(matrix, Matrix4f::scale(100.0, 100.0, 100.0));
		models->ground.getVertexArray().bind();
		models->ground.getProgram().use();
		models->ground.getProgram().setTexture("in_texture", models->ground.getTexture());
		models->ground.getProgram().setMatrix("in_matrix", groundMatrix);
		models->ground.getProgram().draw(GL_TRIANGLES, models->ground.getVertexCount());
		models->ground.getProgram().resetValues();
	}
	catch (OpenglException & e)
	{
		Logger::log(e.getMessage());
		throw e;
	}
}

void GraphicsRenderer::drawGrass(Matrix4f& matrix)
{
	try
	{
		float piPul = (float)(3.1415f / 2);
		Matrix4f rotationMatrix = Matrix4f::yawPitchRoll(-camera.roll, -(((camera.pitch + piPul) / 2) - piPul), -camera.yaw);
		//Matrix4f rotationMatrix = Matrix4f::yawPitchRoll(-camera.roll, piPul, -camera.yaw);

		models->grass.getVertexArray().bind();
		models->grass.getProgram().use();
		models->grass.getProgram().setTexture("in_texture", models->grass.getTexture());
		models->grass.getProgram().setMatrix("in_matrix", matrix);
		models->grass.getProgram().setMatrix("in_matrix_rotation", rotationMatrix);
		models->grass.getProgram().setUniform1f("in_wind_x", wind_x);
		models->grass.getProgram().setUniform1f("in_wind_y", wind_y);
		models->grass.getProgram().drawInstances(GL_TRIANGLES, models->grass.getVertexCount(), grassClumps.size());

		models->grass.getProgram().resetValues();
	}
	catch (OpenglException& e)
	{
		Logger::log(e.getMessage());
		throw e;
	}
}

void GraphicsRenderer::draw2D()
{
	drawFrame();
}

void GraphicsRenderer::drawFrame()
{
	Matrix4f matrix = Matrix4f::multiply(projection2D, Matrix4f::scale(getWidth() / BLEND_FACTOR, getHeight() / BLEND_FACTOR, 1));

	try
	{
		frames->frame2.use();
		models->frame1.getVertexArray().bind();
		models->frame1.getProgram().use();
		models->frame1.getProgram().setMatrix("in_matrix", matrix);
		models->frame1.getProgram().setTexture("in_texture", frames->frame1.getTexture());
		models->frame1.getProgram().draw(GL_TRIANGLES, models->frame1.getVertexCount());
		models->frame1.getProgram().resetValues();
		frames->frame2.unuse();
	}
	catch (OpenglException & e)
	{
		Logger::log(e.getMessage());
		throw e;
	}

	matrix = Matrix4f::multiply(projection2D, Matrix4f::scale(getWidth(), getHeight(), 1));

	try {
		models->frame2.getVertexArray().bind();
		models->frame2.getProgram().use();
		models->frame2.getProgram().setMatrix("in_matrix", matrix);
		models->frame2.getProgram().setTexture("in_texture", frames->frame1.getTexture());
		models->frame2.getProgram().setTexture("in_texture_2", frames->frame2.getTexture());
		models->frame2.getProgram().draw(GL_TRIANGLES, models->frame2.getVertexCount());
		models->frame2.getProgram().resetValues();
	}
	catch (OpenglException & e)
	{
		Logger::log(e.getMessage());
		throw e;
	}
}
