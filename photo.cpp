#include "photo.h"
using namespace std;

const String& Photo::getName() const {
    return name;
}
const PixelMatrix& Photo::getPixels() const {
    return pixels;
}
void Photo::setName(const String& str) {
    name = str;
}
void Photo::setPixels(const PixelMatrix& pxls) {
    pixels = pxls;
}

Photo::Photo() : name("") {
    pixels = PixelMatrix();
}
Photo::Photo(const String& otherName, const PixelMatrix& otherPixels) {
    name = otherName;
    pixels = otherPixels;
}