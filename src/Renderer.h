#pragma once
#include "Palette.h"
#include "Geometry3d.h"
#include "Vec4.h"
#include "Vec3.h"

class Renderer
{
public:
	Renderer(Palette _palette):palette(_palette){}
	void Render();


private:
	struct HitPayload {
		float HitDistance;
		Vec3 WorldPosition;
		Vec3 WorldNormal;
		int Index;
	};

	void PerPixel(int x,int y);
	HitPayload TraceRay(const Ray& ray);
	HitPayload ClosestHit(const Ray& ray, float hitDistance,int objectIndex);
	HitPayload Miss(const Ray& ray);
private:
	Palette palette;
	std::vector<Sphere> spheres;
	
};

