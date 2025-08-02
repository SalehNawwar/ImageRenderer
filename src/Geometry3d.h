#pragma once
#include "Vec4.h"
#include "Vec3.h"
#include "Geometry2d.h"

struct Shape {
	Matrix rotation;
	Vec3 translation;
	Vec4 color;
	float metalic;
	float soft;
	Shape() :rotation(Matrix::Identity(3)),metalic(0),soft(1) {}
	Shape(const Vec3& c) :rotation(Matrix::Identity(3)),translation(c),metalic(0), soft(1) {}
	void translate(const Vec3& v) {
		translation = translation + v;
	}

	void rotate(const Matrix& mat) {
		rotation = mat * rotation;
	}

	virtual void scale(float s) = 0;
};

struct Sphere:Shape {
	
	Sphere() :Shape(), radius(1) {}
	Sphere(Vec3 c,float r):Shape(c),radius(r){}
	void scale(float s) override {
		radius *= s;
	}

	Vec3 Center()const {
		return translation;
	}

	float Radius() const{
		return radius;
	}

private:
	float radius;
};

struct Ray {
	Vec3 origin;
	Vec3 direction;
	Ray(Vec3 orig, Vec3 dir) :origin(orig), direction(dir) {}
	
};
