#include "pixelMatrix.h"
using namespace std;

void PixelMatrix::copyFrom(const PixelMatrix& other) {
    height = other.height;
    width = other.width;
    pixels = new size_t*[height];
    for(size_t i = 0; i < height; i++) {
        pixels[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            pixels[i][j] = other.pixels[i][j];
    }
}
void PixelMatrix::free() {
    for(size_t i = 0; i < height; i++)
        delete[] pixels[i];
    delete[] pixels;
}

size_t** PixelMatrix::getPixels() const {
    return pixels;
}
size_t PixelMatrix::getHeight() const {
    return height;
}
size_t PixelMatrix::getWidth() const {
    return width;
}
void PixelMatrix::setPixels(const size_t* const* pxls) {
    pixels = new size_t*[height]; //shoud i delete before initialize
    for(size_t i = 0; i < height; i++) {
        pixels[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            pixels[i][j] = pxls[i][j];
    }
}
void PixelMatrix::setHeight(size_t height) {
    this->height = height;
}
void PixelMatrix::setWidth(size_t width) {
    this->width = width;
}

PixelMatrix::PixelMatrix() : pixels(nullptr), height(0), width(0) {}
PixelMatrix::PixelMatrix(size_t** pxls, size_t height, size_t width) : height(height), width(width) {
    setPixels(pxls);
}
PixelMatrix& PixelMatrix::operator=(const PixelMatrix& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
PixelMatrix::~PixelMatrix() {
    free();
}