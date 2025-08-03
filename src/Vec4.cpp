#include "Vec4.h"

Vec4 operator*(float val, const Vec4& other) {
	return Vec4(other.x * val, other.y * val, other.z * val, other.w * val);
}

Vec4 operator*(const Vec4& other, float val) {
	return Vec4(other.x * val, other.y * val, other.z * val, other.w * val);
}

Vec4 operator+(float val, const Vec4& other) {
	return Vec4(other.x + val, other.y + val, other.z + val, other.w + val);
}
Vec4 operator+(const Vec4& other, float val) {
	return Vec4(other.x + val, other.y + val, other.z + val, other.w + val);
}

Vec4 operator-(float val, const Vec4& other) {
	return Vec4(val - other.x, val - other.y, val - other.z, val - other.w);
}
Vec4 operator-(const Vec4& other, float val) {
	return Vec4(other.x - val, other.y - val, other.z - val, other.w - val);
}

Vec4 operator*(const Matrix& mat, const Vec4& vec) {
	return Vec4(vec.x * mat._arr[0][0] + vec.y * mat._arr[0][1] + vec.z * mat._arr[0][2] + vec.w * mat._arr[0][3],
		vec.x * mat._arr[1][0] + vec.y * mat._arr[1][1] + vec.z * mat._arr[1][2] + vec.w * mat._arr[1][3],
		vec.x * mat._arr[2][0] + vec.y * mat._arr[2][1] + vec.z * mat._arr[2][2] + vec.w * mat._arr[2][3],
		vec.x * mat._arr[3][0] + vec.y * mat._arr[3][1] + vec.z * mat._arr[3][2] + vec.w * mat._arr[3][3]
	);
}