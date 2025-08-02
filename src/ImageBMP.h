#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Vec4.h"
#include <iostream>

class ImageBMP
{
public:
	ImageBMP() :ptr(nullptr), bmpHeader({}), dibHeader({}) {}

	struct BMPHeader {
		unsigned char magic[2];
		unsigned int fileSize;
		unsigned char reserved[4];
		unsigned int pixelArrayOffset;
		
		std::vector<char> Serialize();

		void Deserialize(char* buffer);
	}bmpHeader;

	struct DIBHeader {
		unsigned int headerSize;
		unsigned int bitmapWidth;
		unsigned int bitmapHeight;
		unsigned short numberOfColorPlanes;
		unsigned short bitsPerPixel;
		unsigned int compressionMethod;
		unsigned int rawBitmapSize;
		unsigned int HResolution;
		unsigned int VResolution;
		unsigned int numberOfPaletteColors;
		unsigned int numberOfImportantColors;
		
		std::vector<char> Serialize();

		void Deserialize(char* buffer);

	}dibHeader;

	void CreateImage(unsigned int width, unsigned int height);
	void SaveImage(const std::string& name);
	void ReadImage(const std::string& name);
	void Paint(const std::vector<std::vector<Vec4> > paint);
	std::vector<std::vector<Vec4> > GetPaint();

	~ImageBMP() {
		if(ptr)delete[] ptr;
	}

private:
	unsigned char *ptr;
};

