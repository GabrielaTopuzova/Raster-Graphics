#include "PGM.h"
#include "PBM.h"

size_t PGM::getWhite() const {
    return white;
}
short PGM::getType() const {
    return 2;
}

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

    for(size_t i = 0; i < height; i++) 
        delete[] result;
    delete[] result;

    return new PBM(getName(), res);
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

    PixelMatrix res(result, width, height);

    for(size_t i = 0; i < width; i++) 
        delete[] result;
    delete[] result;

    return new PGM(getName(), res, white);
}
Photo* PGM::negative() {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            result[i][j] = white - getPixels().getPixels()[i][j];
    }

    PixelMatrix res(result, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] result;
    delete[] result;

    return new PGM(getName(), res, white);  
}
Photo* PGM::clone() const {
    return new PGM(*this);
}

void PGM::readFromFile(ifstream& file) {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    file >> width >> height;
    file >> white;
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            file >> result[i][j];
    }

    PixelMatrix res(result, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] result;
    delete[] result;

    setPixels(res); 
}
void PGM::saveToFile(ofstream& file) const {
    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    file << "P2" << endl;
    file << width << " " << height << endl;
    file << white << endl;
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            file << getPixels().getPixels()[i][j] << " ";
        file << endl;
    }
}

#include"PPM.h"
int main() {
    ifstream in("mami (1).ppm");
    char p1;
    in >> p1 >> p1;
    PPM original("bee.ppm", 255, PixelMatrix(), PixelMatrix(), PixelMatrix());
    original.readFromFile(in);
    in.close();

    ofstream out1("1rotated.ppm");
    original
        .rotate(false)
        ->saveToFile(out1);
    
    out1.close();
    {
        ofstream out("1copied.ppm");
        original
            .saveToFile(out);
        out.close();
    }   
    {
        ofstream out("1negatived.ppm");
        original
            .negative()
            ->saveToFile(out);
        out.close();
    }    
    {
        ofstream out("1gray.ppm");
        original
            .grayscale()
            ->negative()
            ->saveToFile(out);
        out.close();
    }    
    {
        ofstream out("1monochrome.ppm");
        original
            .monochrome()
            ->saveToFile(out);
        out.close();
    }    
}