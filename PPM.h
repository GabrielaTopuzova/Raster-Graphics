#ifndef _PPM
#define _PPM
#include "photo.h"
#include <iostream>
using namespace std;

class PPM : public Photo {
    size_t white;
public:
    PPM(const String&, const PixelMatrix&, size_t);

    Photo* grayscale() override;
    Photo* monochrome() override;
    Photo* rotate(bool) override;
    Photo* negative() override;
    
    void readFromFile(ifstream&) override;
    void saveToFile(ofstream&) const override;
};
#endif