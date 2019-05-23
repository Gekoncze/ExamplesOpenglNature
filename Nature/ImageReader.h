#pragma once
#include <string>
#include <vector>
#include "Opengl.h"

class ImageReader
{
private:
	std::vector<GLubyte> data;
	int width;
	int height;

public:
	ImageReader(std::string path);
	~ImageReader();

	std::vector<GLubyte>& getData()
	{
		return data;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}
};

