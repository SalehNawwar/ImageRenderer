#include "Renderer.h"

//#include <math.h>
void Renderer::Render(const Camera& camera,const Scene& scene) {
	activeCamera = &camera;
	activeScene = &scene;
	std::cout << scene.spheres.size() << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
	Vec4 color;
	for (int x = 0; x < palette->width; ++x) {
		for (int y = 0; y < palette->height; ++y) {
			Vec4 color = PerPixel(x, y, 10);
			
			//for (int i = 0; i < 4; i++)color.Set(i, 0, std::min(color.At(i, 0),1.0f));
			palette->SetPixel(x, y, color);

		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time Elapsed : " << duration.count() << std::endl;
}

Vec4 Renderer::PerPixel(int x, int y, int bounces) const {
	
	const Vec3& origin = activeCamera->Position;
	Vec3 direction(x * Wscale - 1, y * Hscale - 1, -1);
	direction = activeCamera->Orientation* direction;
	Ray ray(origin, direction);

	float multiplier = 1.0f;

	Vec3 color;
	HitPayload payload;

	for (int i = 0; i < bounces; ++i) {
		
		payload = TraceRay(ray);
		if (payload.HitDistance < 0.0f) {
			Vec3 skyColor(0.0f,0.0f,0.0f);
			color = color + skyColor * multiplier;
			break;
		}
		
		float lightIntensity = payload.WorldNormal.Dot(Vec3(-lightDir));
		if (lightIntensity < 0.0f) {
			lightIntensity = 0.0f;
		}
		const Sphere& sphere = activeScene->spheres[payload.Index];
		Vec3 sphereColor = sphere.color * lightIntensity;
		color = color + sphereColor * multiplier;
		multiplier *= 0.7;
		
		ray.origin = payload.WorldPosition + payload.WorldNormal * 0.00001f;
		ray.direction = ray.direction.Reflect(payload.WorldNormal);
	}

	return Vec4(color.x,color.y,color.z, 1);
}

Renderer::HitPayload Renderer::TraceRay(const Ray& ray) const {
	
	float hitDistance = -1.0f;
	int index = -1;
	int closestSphere = -1;
	for (const Sphere& sphere : activeScene->spheres)
	{
		++index;
		// (xcamera + t*xray - cx)^2 + (ycamera + t*yray - cy)^2 +(zcamera + t*zray - cz)^2 = r^2
		// t^2 * dot(ray,ray) + t 2*dot(ray , (camera-c)) + dot((camera-c),(camera-c)) = r^2
		float a = ray.direction.Dot(ray.direction);
		float b = 2 * ray.direction.Dot(Vec3(ray.origin - sphere.Center()));
		float c = Vec3(ray.origin - sphere.Center()).Dot(Vec3(ray.origin - sphere.Center())) - sphere.Radius() * sphere.Radius();
		float delta = b * b - 4 * a * c;
		//std::cout << delta << std::endl;
		if (delta < 0) {
			continue;
		}
		//print(std::cout, ray);
		float t = (-b - sqrtf(delta)) / (2 * a);

		if (t > 0 && (hitDistance > t || hitDistance < 0)) {
			hitDistance = t;
			closestSphere = index;
		}
	}

	if (closestSphere < 0) {
		return Miss(ray);
	}

	return ClosestHit(ray, hitDistance, closestSphere);
}

Renderer::HitPayload Renderer::ClosestHit(const Ray& ray, float hitDistance, int objectIndex) const {
	
	
	HitPayload payload;

	payload.HitDistance = hitDistance;
	payload.Index = objectIndex;
	payload.WorldPosition = ray.origin + ray.direction * hitDistance;
	payload.WorldNormal = payload.WorldPosition - activeScene->spheres[objectIndex].Center();
	/*HitPayload checkShadow = TraceRay(Ray(payload.WorldPosition,-lightDir));
	if(checkShadow.HitDistance >= 0.0f){
		return Miss
	}*/
	return payload;
}

Renderer::HitPayload Renderer::Miss(const Ray& ray) const {
	HitPayload payload;
	payload.HitDistance = -1.0f;
	return payload;
}
