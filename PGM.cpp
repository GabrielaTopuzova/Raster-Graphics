#include "PGM.h"

PGM::PGM(const String& string, const PixelMatrix& pxls, size_t white) : Photo(string, pxls), white(white) {}

Photo* PGM::grayscale() {
    return new PGM(*this);    
}
Photo* PGM::monochrome() {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();
    size_t** result = new size_t*[height];
    
    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            if(getPixels().getPixels()[i][j] > white / 2)
                result[i][j] = 0;
            else
                result[i][j] = 1;
    }

    PixelMatrix res(result, height, width);

    return new PGM(getName(), res, white);
}
Photo* PGM::rotate(bool direction) {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    size_t** result = new size_t*[width];
    for(size_t i = 0; i < width; i++)
        result[i] = new size_t[height];

    if(direction)
        for(size_t i = 0; i < height; i++) 
            for(size_t j = 0; j < width; j++)
                result[j][i] = getPixels().getPixels()[i][width - 1 - j];


    if(!direction)
        for(size_t i = 0; i < height; i++) 
            for(size_t j = 0; j < width; j++)
                result[j][i] = getPixels().getPixels()[height - 1 - i][j];

    PixelMatrix res(result, height, width);
    return new PGM(getName(), res, white);
}
Photo* PGM::negative() {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            result[i][j] = 15 - getPixels().getPixels()[i][j];
    }

    PixelMatrix res(result, height, width);

    return new PGM(getName(), res, white);  
}

void PGM::readFromFile(ifstream& file) {

}
void PGM::saveToFile(ofstream& file) const {

}