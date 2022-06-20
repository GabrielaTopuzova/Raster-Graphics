#ifndef _PHOTO
#define _PHOTO
#include "string.h"
#include "pixelMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

class Photo {
private:
    String name;
    PixelMatrix pixels;
public:
    const String& getName() const;
    const PixelMatrix& getPixels() const;
    void setName(const String&);
    void setPixels(const PixelMatrix&);

    Photo();
    Photo(const String&);
    Photo(const String&, const PixelMatrix&);
    
    virtual size_t getHeight() const = 0;
    virtual size_t getWidth() const = 0;
    virtual size_t getWhite() const = 0;
    virtual short getType() const = 0;
    virtual Photo* grayscale() = 0;
    virtual Photo* monochrome() = 0;
    virtual Photo* rotate(bool) = 0;
    virtual Photo* negative() = 0;
    virtual Photo* clone() const = 0;
    virtual ~Photo() = default;

    virtual PixelMatrix getRed() const;
    virtual PixelMatrix getGreen() const;
    virtual PixelMatrix getBlue() const;

    virtual void readFromFile(ifstream&) = 0;
    virtual void saveToFile(ofstream&) const = 0;
    void save() const;
};
#endif