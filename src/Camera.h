#pragma once
#include "Vec3.h"
#include "Geometry3d.h"

class Camera
{
public:
	Vec3 Position;
	Matrix Orientation;
public:
	Camera():Position(0,0,10),Orientation(Matrix::Identity(3)){}
};

class Scene {
public:
	std::vector<Sphere> spheres;
};