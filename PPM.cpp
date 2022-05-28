#include "PPM.h"

PPM::PPM(const String& string, const PixelMatrix& pxls, size_t white) : Photo(string, pxls), white(white) {}

Photo* PPM::grayscale() {
  
}
Photo* PPM::monochrome() {
    
}
Photo* PPM::rotate(bool direction) {
    
}
Photo* PPM::negative() {
      
}

void PPM::readFromFile(ifstream& file) {

}
void PPM::saveToFile(ofstream& file) const {

}

/*
size_t height = getPixels().getHeight();
size_t width = getPixels().getWidth();
size_t** result = new size_t*[height];

for(size_t i = 0; i < height; i++) {
    result[i] = new size_t[width];
    for(size_t j = 0; j < width; j++)
        result[i][j] = 15 - getPixels().getPixels()[i][j];
}

PixelMatrix res(result, height, width);

return new PPM(getName(), res, white);
*/