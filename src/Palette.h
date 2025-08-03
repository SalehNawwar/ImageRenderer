#pragma once
#include "Vec4.h"

class Palette
{
public:
	int width, height;
	std::vector<std::vector<Vec4> > bitmap;
	Palette(int w, int h);
	Palette(const std::vector<std::vector<Vec4> >& bitmap);

	Vec4 GetPixel(int x, int y);
	void SetPixel(int x, int y,const Vec4& val);

};

