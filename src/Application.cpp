#include <iostream>
#include "Matrix.h"
#include "Vec3.h"
#include "ImageBMP.h";
#include "Palette.h"
#include "Geometry3d.h"
#include "Renderer.h"

void print(std::ostream& stream, const Matrix& mat)
{
	stream << '\n';
	for (int i = 0; i < mat.Rows(); ++i) {
		stream << '[';
		for (int j = 0; j < mat.Columns(); ++j) {
			stream << mat.At(i, j) << "\t";
		}
		stream << "]\n";
	}
	stream << '\n';
}

int main() {
	
	ImageBMP image;
	int w = 2000;
	int h = 2000;
	std::cout << "creating palette" << std::endl;
	Palette palette(w, h);
	Renderer renderer(palette);
	renderer.SetLight(Vec3(0, -1, -1));
	Camera camera;
	camera.Position.z = 3;
	Scene scene;
	std::cout << "drawing circle in palette" << std::endl;
	Sphere sphere1(Vec3(-1, 0, 0),0.9f),sphere2(Vec3(1,0,0),0.9f);
	Vec4 color(0.8, 0.6, 0.4, 1);
	sphere1.color = Vec3(1, 0, 0);
	sphere1.metalic = 0.6;
	sphere1.soft = 1; 
	sphere2.color= Vec3(0, 0, 1);
	sphere2.metalic = 0.3;
	sphere2.soft = 1;
	scene.spheres.push_back(sphere1);
	scene.spheres.push_back(sphere2);
	
	renderer.Render(camera, scene);

	std::cout << "painting palette" << std::endl;
	image.Paint(palette.bitmap);
	std::cout << "saving palette" << std::endl;
	image.SaveImage("sphere.bmp");

	return 0;
}