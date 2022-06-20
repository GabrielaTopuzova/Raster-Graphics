#include "photo.h"

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
Photo::Photo(const String& otherName) : name(otherName) {}
Photo::Photo(const String& otherName, const PixelMatrix& otherPixels) {
    name = otherName;
    pixels = otherPixels;
}

PixelMatrix Photo::getRed() const {
    return PixelMatrix();
}
PixelMatrix Photo::getGreen() const {
    return PixelMatrix();
}
PixelMatrix Photo::getBlue() const {
    return PixelMatrix();
}

void Photo::save() const {
    ofstream out(getName().getStr());
    if(!out.is_open())
        throw "Can't open file";
    saveToFile(out);
}