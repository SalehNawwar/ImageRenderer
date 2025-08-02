#pragma once
#include "Vec3.h"
#include "Geometry3d.h"

class RayTracer
{
public:
	RayTracer() :light(0,-1,0) {}
	RayTracer(Vec3 lightDir) :light(lightDir) { light.Normalize(); }

	Vec4 Trace(Ray ray, int bounce = 0) const;

	float Collide(int sphereIndex,Ray ray) const;
	void AddSphere(Sphere sphere);
private:

	std::vector<Sphere> spheres;
	Vec3 light;
};

