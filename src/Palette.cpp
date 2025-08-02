#include "Palette.h"
Palette::Palette(int w, int h):width(w),height(h){
	bitmap.assign(h, std::vector<Vec4>(w,Vec4(0,0,0,1)));
}

Palette::Palette(const std::vector<std::vector<Vec4> >& arr):width(arr.at(0).size()),height(arr.size()),bitmap(arr) {

}

Vec4 Palette::GetPixel(int x, int y) {
	return bitmap.at(y).at(x);
}

void Palette::SetPixel(int x, int y, Vec4 val) {
	bitmap.at(y).at(x) = val;
}
