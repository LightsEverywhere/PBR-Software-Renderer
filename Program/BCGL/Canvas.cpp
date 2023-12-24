#include "pch.h"
#include "Canvas.h"

CCanvas::CCanvas(const int& width, const int& height)
{
	this->width = width;
	this->height = height;
	frameBuffer = new BYTE[width * height * 4];
	memset(frameBuffer, 52, width * height * 4);
}

CCanvas::~CCanvas()
{
	delete[] frameBuffer;
}

bool CCanvas::CheckRange(const int& x, const int& y)
{
	if (x < width >> 1 && x > -(width >> 1) && y < height >> 1 && y > -(height >> 1))
		return true;
	return false;
}

bool CCanvas::SetPixel(const int& x, const int& y, const CRGB& color)
{
	if (!frameBuffer || !CheckRange(x, y)) { return false; }

	const int position = (height / 2 - y) * width * 4 + (x+width/2) * 4;
	frameBuffer[position] = color.blue * 255;
	frameBuffer[position + 1] = color.green * 255;
	frameBuffer[position + 2] = color.red * 255;
	frameBuffer[position + 3] = 1.0;

	return true;
}
