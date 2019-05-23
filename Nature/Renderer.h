#pragma once
class Renderer
{
private:
	int width = 1;
	int height = 1;

public:
	Renderer();
	virtual ~Renderer();

	int getWidth();
	int getHeight();
	float getAspect();
	void setSize(int width, int height);

	virtual void onCreate() = 0;
	virtual void onResize() = 0;
	virtual void onDraw() = 0;
};
