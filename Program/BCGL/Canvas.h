#pragma once
#include "RGB.h"

class CCanvas
{
public:
	CCanvas() {}
	CCanvas(const int& width, const int& height);
	virtual ~CCanvas();
	bool CheckRange(const int& x, const int& y);
	bool SetPixel(const int& x, const int& y, const CRGB& color);
	BYTE* GetBufferData() const { return frameBuffer; }
public:
	int width, height;

private:
	BYTE* frameBuffer;
};