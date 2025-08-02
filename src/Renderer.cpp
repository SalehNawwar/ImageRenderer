#include "Renderer.h"

void Renderer::PerPixel(int x, int y)
{
}

Renderer::HitPayload Renderer::TraceRay(const Ray& ray)
{
	return HitPayload();
}

Renderer::HitPayload Renderer::ClosestHit(const Ray& ray, float hitDistance, int objectIndex)
{
	return HitPayload();
}

Renderer::HitPayload Renderer::Miss(const Ray& ray)
{
	return HitPayload();
}
