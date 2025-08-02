#pragma once
#include "Vec.h"
class Vec2 : public Vec
{
public:
	Vec2() :Vec({ 0, 0 }) {}
	Vec2(float x, float y) :Vec({ x,y }) {}
	Vec2(const Matrix& mat) : Vec({mat.At(0,0),mat.At(1,0)}) {}
	float X() const { return At(0, 0); }
	float Y() const { return At(1, 0); }
	void SetX(float x) { Set(0, 0, x); }
	void SetY(float y) { Set(1, 0, y); }
	
	float Cross(const Vec2& other) const { return X() * other.Y() - Y() * other.X(); }
};

