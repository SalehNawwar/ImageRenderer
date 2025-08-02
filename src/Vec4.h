#pragma once
#include "Vec.h"
class Vec4 :
    public Vec
{

public:
	Vec4() :Vec({ 0, 0, 0, 0 }) {}
	Vec4(float x, float y, float z, float w) :Vec({ x,y,z,w }) {}
	Vec4(const Matrix& mat) :Vec({ mat.At(0,0),mat.At(1,0),mat.At(2,0),mat.At(3,0)}) {}
	float X() const { return At(0, 0); }
	float Y() const { return At(1, 0); }
	float Z() const { return At(2, 0); }
	float W() const { return At(3, 0); }
	void SetX(float x) { Set(0, 0, x); }
	void SetY(float y) { Set(1, 0, y); }
	void SetZ(float z) { Set(2, 0, z); }
	void SetW(float w) { Set(3, 0, w); }
	

};

