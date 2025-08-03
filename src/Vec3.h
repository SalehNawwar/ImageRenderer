#pragma once
#include "Matrix.h"
struct Vec3
{
	float x, y, z;
	Vec3() : x(0),y(0),z(0) {}
	Vec3(float x, float y, float z) :x(x),y(y),z(z) {}
	Vec3(const Vec3&) = default;
	float Norm() {
		return sqrtf(x * x + y * y + z * z);
	}

	void Normalize() {
		float val = 1 / Norm();
		x *= val;
		y *= val;
		z *= val;
	}

	float Dot(const Vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vec3 Cross(const Vec3& other) const { 
		return Vec3(
			y * other.z - z * other.y,
			-x * other.z + z * other.x,
			x*other.y - y*other.x
			);
	}

	Vec3 Reflect(const Vec3& normal);

	Vec3 operator+(const Vec3& other) const {
		return Vec3(other.x + x, other.y + y, other.z + z);
	}
	Vec3 operator-(const Vec3& other) const {
		return Vec3(x-other.x, y-other.y , z-other.z);
	}
	Vec3 operator/(float val) const {
		val = 1 / val;
		return Vec3(x * val, y * val, z * val);
	}

	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}
};

Vec3 operator*(float val, const Vec3& other);
Vec3 operator*(const Vec3& other, float val);
Vec3 operator+(float val, const Vec3& other);
Vec3 operator+(const Vec3& other, float val);
Vec3 operator-(float val, const Vec3& other);
Vec3 operator-(const Vec3& other, float val);
Vec3 operator*(const Matrix& mat, const Vec3& vec);