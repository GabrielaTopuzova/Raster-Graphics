#ifndef _PBM
#define _PBM
#include "photo.h"
#include <iostream>
using namespace std;

class PBM : public Photo {
public:
    size_t getWhite() const override;
    short getType() const override;
    PBM(const String&, const PixelMatrix&);

    Photo* grayscale() override;
    Photo* monochrome() override;
    Photo* rotate(bool) override;
    Photo* negative() override;
    Photo* clone() const override;

    void readFromFile(ifstream&) override;
    void saveToFile(ofstream&) const override;
};
#endif