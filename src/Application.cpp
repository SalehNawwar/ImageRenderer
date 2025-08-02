#include <iostream>
#include "Matrix.h"
#include "Vec3.h"
#include "ImageBMP.h";
#include "Palette.h"
#include "Geometry3d.h"
#include "RayTracer.h"

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

void DrawCircle(Palette &palette) {
	
	float r = 150;
	float cx = 250;
	float cy = 250;
	for (int x =cx-r; x <= cx + r; ++x) {
		for (int y =cy-r; y <= cy + r; ++y) {
			if((x-cx)* (x - cx)+ (y - cy)* (y - cy)<=r*r)palette.SetPixel(x, y, { 1,0,0,1 });
		}
	}
}

void DrawSphere(Palette& palette,const RayTracer& tracer) {
	Vec3 camera(0, 0, +3);
	for (int x = 0; x < palette.width; ++x) {
		for (int y = 0; y < palette.height; ++y) {
			Vec3 ray(x*2.0f/palette.width-1, y*2.0f/palette.height-1, -1);
			

			palette.SetPixel(x, y, tracer.Trace(Ray(camera,ray),0));
		}
	}
}

int main() {
	
	ImageBMP image;
	int w = 600;
	int h = 600;
	std::cout << "creating palette" << std::endl;
	Palette palette(w, h);
	
	std::cout << "drawing circle in palette" << std::endl;
	RayTracer tracer(Vec3(0,-1,-1));
	Sphere sphere1(Vec3(0, 0, 0), 0.7f),sphere2(Vec3(1,0,-0.3),0.7f);
	Vec4 color(0.8, 0.6, 0.4, 1);
	sphere1.color = Vec4(1, 0, 0, 1);
	sphere1.metalic = 0.6;
	sphere1.soft = 1; 
	sphere2.color= Vec4(0, 0, 1, 1);
	sphere2.metalic = 0.3;
	sphere2.soft = 1;
	tracer.AddSphere(sphere1);
	tracer.AddSphere(sphere2);
	

	DrawSphere(palette, tracer);
	
	std::cout << "painting palette" << std::endl;
	image.Paint(palette.bitmap);
	std::cout << "saving palette" << std::endl;
	image.SaveImage("sphere.bmp");

	return 0;
}