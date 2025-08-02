#include "RayTracer.h"
#include <iostream>

Vec4 RayTracer::Trace(Ray ray,int bounce) const {
	ray.direction.Normalize();
	float nearest = -1;
	int nearestIndex = -1;
	for (int index = 0; index < spheres.size(); ++index) {
		float dist = Collide(index,ray);
		if (dist <= 0)continue;
		if (nearestIndex < 0 || dist < nearest)nearest = dist,nearestIndex=index;
	}

	// collide with object show it
	if (nearestIndex >= 0 && bounce==0) {
		Vec4 color = spheres[nearestIndex].color;
		float metal = spheres[nearestIndex].metalic;
		float soft = spheres[nearestIndex].soft;
		Vec3 point = ray.origin + ray.direction * nearest;
		Vec3 normal = point - spheres[nearestIndex].Center();
		normal.Normalize();
		float factor = -normal.Dot(light);
		if (factor < 0)factor = 0;
		color = (color*(1-metal)+Vec4(1,1,1,1)*metal)*factor;
		
		//std::cout << color.X() << std::endl;
		color.SetW(1);
		return color;
	}

	//// collide and can bounce
	//if (nearestIndex >= 0 && bounce>1) {
	//	//return Vec4(0.7, 0, 1, 1);
	//	Vec3 newOrig = ray.origin + ray.direction * nearest;
	//	Vec3 c = spheres[nearestIndex].Center();
	//	Vec3 norm = newOrig - c;
	//	norm.Normalize();

	//	Vec3 newDir = ray.direction - 2*ray.direction.Dot((Vec3) (-norm));
	//	newDir.Normalize();
	//	Ray newRay(newOrig + norm * 0.0001f, newDir);
	//	float metal = spheres[nearestIndex].metalic;
	//	float soft = spheres[nearestIndex].soft;

	//	return Trace(newRay, bounce - 1)* soft * metal + spheres[nearestIndex].color*(1 - metal)* Trace(Ray(newOrig, -light), 0).Norm() * light.Dot(newRay.direction);
	//}

	return Vec4(0, 0, 0, 1);
}

float RayTracer::Collide(int sphereIndex, Ray ray) const {
	Sphere sphere = spheres[sphereIndex];
	// (xcamera + t*xray - cx)^2 + (ycamera + t*yray - cy)^2 +(zcamera + t*zray - cz)^2 = r^2
	// t^2 * dot(ray,ray) + t 2*dot(ray , (camera-c)) + dot((camera-c),(camera-c)) = r^2
	float a = ray.direction.Dot(ray.direction);
	float b = 2 * ray.direction.Dot(Vec3(ray.origin-sphere.Center()));
	float c = Vec3(ray.origin-sphere.Center()).Dot(Vec3(ray.origin-sphere.Center())) - sphere.Radius() * sphere.Radius();
	float delta = b * b - 4 * a * c;
	//std::cout << delta << std::endl;
	if (delta < 0) {
		return -1;
	}
	//print(std::cout, ray);
	float t = (-b - sqrtf(delta)) / (2 * a);
	return t;
}

void RayTracer::AddSphere(Sphere sphere) {
	spheres.push_back(sphere);
}