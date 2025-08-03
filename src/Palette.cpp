#include "Palette.h"
Palette::Palette(int w, int h):width(w),height(h){
	bitmap.assign(h, std::vector<Vec4>(w));
}

Palette::Palette(const std::vector<std::vector<Vec4> >& arr):width(arr[0].size()),height(arr.size()),bitmap(arr) {

}

Vec4 Palette::GetPixel(int x, int y) {
	return bitmap[y][x];
}

void Palette::SetPixel(int x, int y, const Vec4& val) {
	bitmap[y][x] = val;
}
