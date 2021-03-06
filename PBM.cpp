#include "PBM.h"

size_t PBM::getHeight() const {
    return getPixels().getHeight();
}
size_t PBM::getWidth() const {
    return getPixels().getWidth();
}

size_t PBM::getWhite() const {
    return 1;
}
short PBM::getType() const {
    return 1;
}

PBM::PBM(const String& string) : Photo(string) {
    ifstream in(string.getStr());
    if(!in.is_open())
        throw "Can't open file";
    readFromFile(in);
}
PBM::PBM(const String& otherName, const PixelMatrix& pxls) : Photo(otherName, pxls) {}

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

    PixelMatrix res(result, width, height);

    for(size_t i = 0; i < width; i++) 
        delete[] result[i];
    delete[] result;

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

    for(size_t i = 0; i < height; i++) 
        delete[] result[i];
    delete[] result;

    return new PBM(getName(), res);        
}
Photo* PBM::clone() const {
    return new PBM(*this);
}

void PBM::readFromFile(ifstream& file) {
    char a;
    file >> a >> a;
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    file >> width >> height;
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            file >> result[i][j];
    }

    PixelMatrix res(result, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] result[i];
    delete[] result;

    setPixels(res);    
}
void PBM::saveToFile(ofstream& file) const {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    file << "P1" << endl;
    file << width << " " << height << endl;
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            file << getPixels().getPixels()[i][j] << " ";
        file << endl;
    }
}