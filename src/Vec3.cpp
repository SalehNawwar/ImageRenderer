#include "Vec3.h"

Vec3 operator*(float val, const Vec3& other) {
	return Vec3(other.x * val, other.y * val, other.z * val);
}

Vec3 operator*(const Vec3& other, float val) {
	return Vec3(other.x * val, other.y * val, other.z * val);
}

Vec3 operator+(float val, const Vec3& other) {
	return Vec3(other.x + val, other.y + val, other.z + val);
}
Vec3 operator+(const Vec3& other, float val) {
	return Vec3(other.x + val, other.y + val, other.z + val);
}

Vec3 operator-(float val, const Vec3& other) {
	return Vec3(val - other.x, val - other.y, val - other.z);
}
Vec3 operator-(const Vec3& other, float val) {
	return Vec3(other.x - val, other.y - val, other.z - val);
}

Vec3 operator*(const Matrix& mat, const Vec3& vec) {
	return Vec3(vec.x * mat._arr[0][0] + vec.y * mat._arr[0][1] + vec.z * mat._arr[0][2],
		vec.x * mat._arr[1][0] + vec.y * mat._arr[1][1] + vec.z * mat._arr[1][2],
		vec.x * mat._arr[2][0] + vec.y * mat._arr[2][1] + vec.z * mat._arr[2][2]);
}

Vec3 Vec3::Reflect(const Vec3& normal) {

	const Vec3 parallel = normal * -this->Dot(normal);

	return parallel + (parallel + (*this));
}