#ifndef _PIXELMATRIX
#define _PIXELMATRIL
#include <iostream>
using namespace std;

class PixelMatrix {
private:
    size_t** pixels;
    size_t height;
    size_t width;

    void copyFrom(const PixelMatrix&);
    void free();
public:
    size_t** getPixels() const;
    size_t getHeight() const;//shout i return const sizet
    size_t getWidth() const;
    void setPixels(const size_t* const*);
    void setHeight(size_t);
    void setWidth(size_t);

    PixelMatrix();
    PixelMatrix(size_t**, size_t, size_t);
    PixelMatrix(const PixelMatrix&);
    PixelMatrix& operator=(const PixelMatrix&);
    virtual ~PixelMatrix();
};
#endif