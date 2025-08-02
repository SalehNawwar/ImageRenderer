#pragma once
#include "Palette.h"
#include "Geometry3d.h"
#include "Vec4.h"
#include "Vec3.h"
#include "Camera.h"
#include <iostream>

class Renderer
{
public:
	Renderer(Palette& _palette):palette(&_palette),activeCamera(nullptr),activeScene(nullptr), lightDir(1, -1, -1) {
		lightDir.Normalize();
		
	}
	void Render(const Camera& camera,const Scene& scene);


private:
	struct HitPayload {
		float HitDistance;
		Vec3 WorldPosition;
		Vec3 WorldNormal;
		int Index;
	};

	Vec4 PerPixel(int x,int y, int bounces) const;
	HitPayload TraceRay(const Ray& ray) const;
	HitPayload ClosestHit(const Ray& ray, float hitDistance,int objectIndex)const;
	HitPayload Miss(const Ray& ray)const;


private:
	Palette *palette;
	const Camera* activeCamera;
	const Scene *activeScene;
	Vec3 lightDir;
};

