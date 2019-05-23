#pragma once
#include "Opengl.h"
#include <qopenglwidget.h>
#include <qtimer.h>
#include "GraphicsRenderer.h"

class GraphicsWidget : public QOpenGLWidget
{
	Q_OBJECT

private:
	GraphicsRenderer renderer;
	QTimer timer;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool moveHigher = false;
	bool moveLower = false;
	bool drag = false;
	int dragX = 0;
	int dragY = 0;
	int moveX = 0;
	int moveY = 0;
	float dragCamYaw = 0;
	float dragCamPitch = 0;
    float windDirection = 45*3.1415/180;
    float windSpeed = 0;
    struct osn_context* noise;

public:
	GraphicsWidget(QWidget* parent);
	~GraphicsWidget();

protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);

private:
	void rotateCamera();
	void moveCamera();
	void updateWind();

private slots:
	void stepEvent();
};

