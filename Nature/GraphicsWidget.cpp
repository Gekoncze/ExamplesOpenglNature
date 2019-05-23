#include <GL/glew.h>
#include "GraphicsWidget.h"
#include "Logger.h"
#include "StringUtilities.h"
#include <qevent.h>
#include "open-simplex-noise.h"
#include <chrono>

using namespace cz_mg_logger;

GraphicsWidget::GraphicsWidget(QWidget* parent) : QOpenGLWidget(parent), timer(this)
{
	Logger::log("Graphics widget constructor!");

	QSurfaceFormat format;
	format.setMajorVersion(4);
	format.setMinorVersion(3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setOption(QSurfaceFormat::DebugContext);
	setFormat(format);

	timer.setInterval(25);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(stepEvent()));

	setMouseTracking(true);
	setFocus();

    open_simplex_noise(77374, &noise);
}

GraphicsWidget::~GraphicsWidget()
{
    open_simplex_noise_free(noise);
}

void GraphicsWidget::initializeGL()
{
	renderer.onCreate();
	timer.start();
	Logger::log("Timer started!");
}

void GraphicsWidget::resizeGL(int w, int h)
{
	renderer.setSize(w, h);
	renderer.onResize();
	Logger::log(std::string("resized to ") + w + " " + h);
}

void GraphicsWidget::paintGL()
{
	renderer.onDraw();
}

void GraphicsWidget::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_A) moveLeft = true;
	if (e->key() == Qt::Key_D) moveRight = true;
	if (e->key() == Qt::Key_W) moveUp = true;
	if (e->key() == Qt::Key_S) moveDown = true;
	if (e->key() == Qt::Key_Space) moveHigher = true;
	if (e->key() == Qt::Key_Control) moveLower = true;
}

void GraphicsWidget::keyReleaseEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_A) moveLeft = false;
	if (e->key() == Qt::Key_D) moveRight = false;
	if (e->key() == Qt::Key_W) moveUp = false;
	if (e->key() == Qt::Key_S) moveDown = false;
	if (e->key() == Qt::Key_Space) moveHigher = false;
	if (e->key() == Qt::Key_Control) moveLower = false;
}

void GraphicsWidget::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::MouseButton::LeftButton)
	{
		drag = true;
		dragX = e->x();
		dragY = e->y();
		dragCamYaw = renderer.getCamera().yaw;
		dragCamPitch = renderer.getCamera().pitch;
	}
}

void GraphicsWidget::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::MouseButton::LeftButton) drag = false;
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent* e)
{
	moveX = e->x();
	moveY = e->y();
}

void GraphicsWidget::rotateCamera()
{
	if (drag)
	{
		int dx = moveX - dragX;
		int dy = moveY - dragY;
		renderer.getCamera().yaw = dragCamYaw + dx / 300.0f;
		renderer.getCamera().pitch = dragCamPitch + dy / 300.0f;
	}
}

void GraphicsWidget::moveCamera()
{
	const float speed = 3.0f;
	float mx = moveLeft != false ? -1 : 0 + moveRight != false ? 1 : 0;
	float my = moveUp != false ? 1 : 0 + moveDown != false ? -1 : 0;
	float length = sqrt(mx * mx + my * my);
	if (length > 0)
	{
		mx = mx * speed / length;
		my = my * speed / length;
		renderer.addPosition(mx, my);
	}

	float raise = 0;
	if (moveHigher) raise += speed;
	if (moveLower) raise -= speed;
	renderer.getCamera().z += raise;
}

void GraphicsWidget::updateWind()
{
    auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    windSpeed = 3 * (1 + open_simplex_noise2(noise, millis / 1000.0, 0));
    renderer.setWind(
        windSpeed * cos(windDirection),
        windSpeed * sin(windDirection)
    );
}

void GraphicsWidget::stepEvent()
{
	rotateCamera();
	moveCamera();
	updateWind();
	
	repaint();
}