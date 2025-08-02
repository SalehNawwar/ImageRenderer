#pragma once
#include "Vec.h"
class Vec3 : public Vec
{
public:
	Vec3() :Vec({ 0, 0, 0 }) {}
	Vec3(float x, float y, float z) :Vec({ x,y,z }) {}
	Vec3(const Matrix& mat):Vec({mat.At(0,0),mat.At(1,0),mat.At(2,0)}){}
	float X() const { return At(0, 0); }
	float Y() const { return At(1, 0); }
	float Z() const { return At(2, 0); }
	void SetX(float x) { Set(0, 0, x); }
	void SetY(float y) { Set(1, 0, y); }
	void SetZ(float z) { Set(2, 0, z); }
	Vec3 Cross(const Vec3& other) const { 
		return Vec3({
			Y() * other.Z() - Z() * other.Y(),
			-X() * other.Z() + Z() * other.X(),
			X()*other.Y() - Y()*other.X()
			});
	}
};

