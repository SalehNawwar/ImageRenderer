#pragma once
#include "Matrix.h"
struct Vec4
{
	float x, y, z,w;
	Vec4() : x(0), y(0), z(0),w(0) {}
	Vec4(float x, float y, float z,float w) :x(x), y(y), z(z),w(w) {}

	Vec4 operator+(const Vec4& other) const {
		return Vec4(other.x + x, other.y + y, other.z + z, other.w+w);
	}
	Vec4 operator-(const Vec4& other) const {
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	Vec4 operator/(float val) const {
		val = 1 / val;
		return Vec4(x * val, y * val, z * val, w * val);
	}

	Vec4 operator-() const {
		return Vec4(-x, -y, -z,-w);
	}
};

Vec4 operator*(float val, const Vec4& other);

Vec4 operator*(const Vec4& other, float val);

Vec4 operator+(float val, const Vec4& other);
Vec4 operator+(const Vec4& other, float val);

Vec4 operator-(float val, const Vec4& other);
Vec4 operator-(const Vec4& other, float val);

Vec4 operator*(const Matrix& mat, const Vec4& vec);