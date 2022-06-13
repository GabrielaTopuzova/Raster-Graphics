#ifndef _PGM
#define _PGM
#include "photo.h"
#include <iostream>
using namespace std;

class PGM : public Photo {
    size_t white;
public:
    size_t getWhite() const override;
    short getType() const override;
    PGM(const String&, const PixelMatrix&, size_t);

    Photo* grayscale() override;
    Photo* monochrome() override;
    Photo* rotate(bool) override;
    Photo* negative() override;
    Photo* clone() const override;
    
    void readFromFile(ifstream&) override;
    void saveToFile(ofstream&) const override;
};
#endif