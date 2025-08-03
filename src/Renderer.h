#pragma once
#include "Palette.h"
#include "Geometry3d.h"
#include "Vec4.h"
#include "Vec3.h"
#include "Camera.h"
#include <iostream>
#include <chrono>

class Renderer
{
public:
	Renderer(Palette& _palette):palette(&_palette),activeCamera(nullptr),activeScene(nullptr), lightDir(0, -1, -1),Wscale(2.0f/palette->width),Hscale(2.0f / palette->height) {
		lightDir.Normalize();
		
	}
	void Render(const Camera& camera,const Scene& scene);
	void SetLight(const Vec3& dir) {
		lightDir = dir;
		lightDir.Normalize();
	}

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
	float Wscale, Hscale;
};

