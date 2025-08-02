#include "ImageBMP.h"

void ImageBMP::CreateImage(unsigned int width,unsigned int height) {
	
	dibHeader.headerSize = 40;
	dibHeader.bitmapWidth = width;
	dibHeader.bitmapHeight = height;
	dibHeader.numberOfColorPlanes = 1;
	dibHeader.bitsPerPixel = 32;
	dibHeader.compressionMethod = 0;
	dibHeader.rawBitmapSize = dibHeader.bitmapWidth * dibHeader.bitmapHeight * (dibHeader.bitsPerPixel >> 3);
	dibHeader.HResolution = 2835;
	dibHeader.VResolution = 2835;
	dibHeader.numberOfPaletteColors = 0;
	dibHeader.numberOfImportantColors = 0;

	bmpHeader.magic[0] = 'B';
	bmpHeader.magic[1] = 'M';
	bmpHeader.fileSize = dibHeader.headerSize + dibHeader.rawBitmapSize + 14;
	bmpHeader.pixelArrayOffset = dibHeader.headerSize + 14;
	if (ptr)delete[] ptr;
	ptr = new unsigned char[dibHeader.rawBitmapSize];
	memset(ptr, 125, dibHeader.rawBitmapSize);
}

void ImageBMP::SaveImage(const std::string& name) {
	std::ofstream imageFile(name, std::ios::binary);
	
	std::vector<char> buffer = bmpHeader.Serialize();
	imageFile.write(buffer.data(), buffer.size());

	buffer = dibHeader.Serialize();
	imageFile.write(buffer.data(), buffer.size());

	imageFile.write((char*)ptr, dibHeader.rawBitmapSize);
	imageFile.close();
}

void ImageBMP::ReadImage(const std::string& name) {
	std::ifstream imageFile(name, std::ios::binary);
	
	if (!imageFile) {
		throw -1;
	}
	char buffer[54];
	imageFile.read(buffer, 54);
	
	bmpHeader.Deserialize(buffer);
	dibHeader.Deserialize(buffer + 14);
	if (ptr)delete[] ptr;
	ptr = new unsigned char[dibHeader.rawBitmapSize];
	imageFile.read((char*)ptr, dibHeader.rawBitmapSize);
	imageFile.close();

}

std::vector<char> ImageBMP::BMPHeader::Serialize() {
	std::vector<char> buffer;

	buffer.resize(14);
	buffer[0] = magic[0];
	buffer[1] = magic[1];
	for (int i = 0; i < 4; i++) {
		buffer[2 + i] = (fileSize >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[6 + i] = reserved[i];
	}
	for (int i = 0; i < 4; i++) {
		buffer[10 + i] = (pixelArrayOffset >> (8 * i)) & 255;
	}

	return buffer;
}

void ImageBMP::BMPHeader::Deserialize(char* buffer) {
	memcpy(magic, buffer, 2);
	for (int i = 0; i < 4; ++i) {
		fileSize |= (unsigned int)buffer[i + 2] << (8 * i);
	}
	memcpy(reserved, buffer + 6, 4);
	for (int i = 0; i < 4; ++i) {
		pixelArrayOffset |= (unsigned int)buffer[i + 10] << (8 * i);
	}
}

std::vector<char> ImageBMP::DIBHeader::Serialize() {
	std::vector<char> buffer;

	buffer.resize(headerSize);

	for (int i = 0; i < 4; i++) {
		buffer[i] = (headerSize >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[4 + i] = (bitmapWidth >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[8 + i] = (bitmapHeight >> (8 * i)) & 255;
	}
	for (int i = 0; i < 2; i++) {
		buffer[12 + i] = (numberOfColorPlanes >> (8 * i)) & 255;
	}
	for (int i = 0; i < 2; i++) {
		buffer[14 + i] = (bitsPerPixel >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[16 + i] = (compressionMethod >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[20 + i] = (rawBitmapSize >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[24 + i] = (HResolution >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[28 + i] = (VResolution >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[32 + i] = (numberOfPaletteColors >> (8 * i)) & 255;
	}
	for (int i = 0; i < 4; i++) {
		buffer[36 + i] = (numberOfImportantColors >> (8 * i)) & 255;
	}

	return buffer;
}

void ImageBMP::DIBHeader::Deserialize(char* buffer) {

	for (int i = 0; i < 4; i++) {
		headerSize |= (unsigned int)buffer[i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		bitmapWidth |= (unsigned int)buffer[4 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		bitmapHeight |= (unsigned int)buffer[8 + i] << (8 * i);
	}
	for (int i = 0; i < 2; i++) {
		numberOfColorPlanes |= (unsigned int)buffer[12 + i] << (8 * i);
	}
	for (int i = 0; i < 2; i++) {
		bitsPerPixel |= (unsigned int)buffer[14 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		compressionMethod |= (unsigned int)buffer[16 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		rawBitmapSize |= (unsigned int)buffer[20 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		HResolution |= (unsigned int)buffer[24 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		VResolution |= (unsigned int)buffer[28 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		numberOfPaletteColors |= (unsigned int)buffer[32 + i] << (8 * i);
	}
	for (int i = 0; i < 4; i++) {
		buffer[36 + i] = (numberOfImportantColors >> (8 * i)) & 255;
		numberOfImportantColors |= (unsigned int)buffer[36 + i] << (8 * i);
	}
}

void ImageBMP::Paint(const std::vector<std::vector<Vec4> > paint) {
	int w = paint.at(0).size();
	int h = paint.size();

	CreateImage(w, h);
	
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			float r = paint.at(i).at(j).At(0, 0);
			float g = paint.at(i).at(j).At(1, 0);
			float b = paint.at(i).at(j).At(2, 0);
			float a = paint.at(i).at(j).At(3, 0);
			ptr[(i * w + j) * 4] = (int)(b * 255);
			ptr[(i * w + j) * 4 + 1] = (int)(g * 255);
			ptr[(i * w + j) * 4 + 2] = (int)(r * 255);
			ptr[(i * w + j) * 4 + 3] = (int)(a * 255);

		}
	}
}

std::vector<std::vector<Vec4> > ImageBMP::GetPaint() {
	int w = dibHeader.bitmapWidth;
	int h = dibHeader.bitmapHeight;
	std::vector<std::vector<Vec4> > paint(h,std::vector<Vec4>(w));

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++i) {
			for (int k = 0; k < 4; ++k) {
				float val = ptr[(i * w + j) * 4 + k];
				paint.at(i).at(j).Set(k, 0, val/255);
			}
		}
	}

	return paint;
}