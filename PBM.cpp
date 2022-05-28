#include "PBM.h"

Photo* PBM::grayscale() {
    return new PBM(*this);
}
Photo* PBM::monochrome() {
    return new PBM(*this);    
}
Photo* PBM::rotate(bool direction) {
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
    return new PBM(getName(), res);
}
Photo* PBM::negative() {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            if(getPixels().getPixels()[i][j] == 0)
                result[i][j] = 1;
            else
                result[i][j] = 0;
    }

    PixelMatrix res(result, height, width);

    return new PBM(getName(), res);        
}

void PBM::readFromFile(ifstream& file) {

}
void PBM::saveToFile(ofstream& file) const {

}