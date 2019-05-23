#include "ImageReader.h"
#include <qpixmap.h>
#include <qimage.h>
#include <vector>
#include "IOException.h"

ImageReader::ImageReader(std::string path)
{
	int bpp = 4;

	QImage qimage;
	if (!qimage.load(QString(path.c_str()))) throw IOException("Could not load image " + path + ".");

	data.resize(qimage.width() * qimage.height() * bpp);
	width = qimage.width();
	height = qimage.height();

	int i = 0;
	for (int y = qimage.height() - 1; y >= 0; y--)
	{
		for (int x = 0; x < qimage.width(); x++)
		{
			QRgb c = qimage.pixel(x, y);
			data.at(i + 0) = qRed(c);
			data.at(i + 1) = qGreen(c);
			data.at(i + 2) = qBlue(c);
			data.at(i + 3) = qAlpha(c);
			i += bpp;
		}
	}
}

ImageReader::~ImageReader()
{	
}
