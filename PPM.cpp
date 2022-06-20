#include "PPM.h"
#include "PGM.h"
#include "PBM.h"

size_t PPM::getHeight() const {
    return redMatrix.getHeight();
}
size_t PPM::getWidth() const {
    return redMatrix.getWidth();
}

PixelMatrix PPM::getRed() const {
    return redMatrix;
}
PixelMatrix PPM::getGreen() const {
    return greenMatrix;
}
PixelMatrix PPM::getBlue() const {
    return blueMatrix;
}

size_t PPM::getWhite() const {
    return white;
}
short PPM::getType() const {
    return 3;
}

PPM::PPM(const String& string) : Photo(string) {
    ifstream in(string.getStr());
    if(!in.is_open())
        throw "Can't open file";
    readFromFile(in);
}
PPM::PPM(const String& string, size_t white, const PixelMatrix& red, const PixelMatrix& green, const PixelMatrix& blue) : 
            Photo(string), white(white), redMatrix(red), greenMatrix(green), blueMatrix(blue) {}

Photo* PPM::grayscale() {
    size_t height = redMatrix.getHeight();
    size_t width = redMatrix.getWidth();
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            result[i][j] = (redMatrix.getPixels()[i][j] + greenMatrix.getPixels()[i][j] + blueMatrix.getPixels()[i][j]) / 3;
    }

    PixelMatrix res(result, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] result[i];
    delete[] result;

    return new PGM(getName(), res, white);
}
Photo* PPM::monochrome() {
    size_t height = redMatrix.getHeight();
    size_t width = redMatrix.getWidth();
    size_t** result = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        result[i] = new size_t[width];
        for(size_t j = 0; j < width; j++)
            if(redMatrix.getPixels()[i][j] + greenMatrix.getPixels()[i][j] + blueMatrix.getPixels()[i][j] > 3 * white / 2)
                result[i][j] = 0;
            else 
                result[i][j] = 1;
    }

    PixelMatrix res(result, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] result[i];
    delete[] result;

    return new PBM(getName(), res);
}
Photo* PPM::rotate(bool direction) {
    size_t height = redMatrix.getHeight();
    size_t width = redMatrix.getWidth();
    size_t** red = new size_t*[width];
    size_t** green = new size_t*[width];
    size_t** blue = new size_t*[width];
    
    for(size_t i = 0; i < width; i++) {
        red[i] = new size_t[height];
        green[i] = new size_t[height];
        blue[i] = new size_t[height];
    }

    if(direction)
        for(size_t i = 0; i < height; i++) 
            for(size_t j = 0; j < width; j++) {
                red[j][i] = redMatrix.getPixels()[i][width - 1 - j];
                green[j][i] = greenMatrix.getPixels()[i][width - 1 - j];
                blue[j][i] = blueMatrix.getPixels()[i][width - 1 - j];
            }


    if(!direction)
        for(size_t i = 0; i < height; i++) 
            for(size_t j = 0; j < width; j++) {
                red[j][i] = redMatrix.getPixels()[height - 1 - i][j];
                green[j][i] = greenMatrix.getPixels()[height - 1 - i][j];
                blue[j][i] = blueMatrix.getPixels()[height - 1 - i][j];
            }

    PixelMatrix resRed(red, width, height);
    PixelMatrix resGreen(green, width, height);
    PixelMatrix resBlue(blue, width, height);

    for(size_t i = 0; i < width; i++) 
        delete[] red;
    delete[] red;
    for(size_t i = 0; i < width; i++) 
        delete[] green;
    delete[] green;
    for(size_t i = 0; i < width; i++) 
        delete[] blue;
    delete[] blue;

    return new PPM(getName(), white, resRed, resGreen, resBlue);
}
Photo* PPM::negative() {
    size_t height = redMatrix.getHeight();
    size_t width = redMatrix.getWidth();
    size_t** red = new size_t*[height];
    size_t** green = new size_t*[height];
    size_t** blue = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        red[i] = new size_t[width];
        green[i] = new size_t[width];
        blue[i] = new size_t[width];
        for(size_t j = 0; j < width; j++) {
            red[i][j] = white - redMatrix.getPixels()[i][j];
            green[i][j] = white - greenMatrix.getPixels()[i][j];
            blue[i][j] = white - blueMatrix.getPixels()[i][j];
        }
    }

    PixelMatrix resRed(red, height, width);
    PixelMatrix resGreen(green, height, width);
    PixelMatrix resBlue(blue, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] red;
    delete[] red;
    for(size_t i = 0; i < height; i++) 
        delete[] green;
    delete[] green;
    for(size_t i = 0; i < height; i++) 
        delete[] blue;
    delete[] blue;

    return new PPM(getName(), white, resRed, resGreen, resBlue);
}
Photo* PPM::clone() const {
    return new PPM(*this);
}

void PPM::readFromFile(ifstream& file) {
    char a;
    file >> a >> a;

    size_t height = getPixels().getHeight();
    size_t width = getPixels().getWidth();

    file >> width >> height;
    file >> white;
    size_t** red = new size_t*[height];
    size_t** green = new size_t*[height];
    size_t** blue = new size_t*[height];

    for(size_t i = 0; i < height; i++) {
        red[i] = new size_t[width];
        green[i] = new size_t[width];
        blue[i] = new size_t[width];
        for(size_t j = 0; j < width; j++) {
            file >> red[i][j] >> green[i][j] >> blue[i][j];
        }
    }
    redMatrix = PixelMatrix(red, height, width);
    greenMatrix = PixelMatrix(green, height, width);
    blueMatrix = PixelMatrix(blue, height, width);

    for(size_t i = 0; i < height; i++) 
        delete[] red[i];
    delete[] red;
    for(size_t i = 0; i < height; i++) 
        delete[] green[i];
    delete[] green;
    for(size_t i = 0; i < height; i++) 
        delete[] blue[i];
    delete[] blue;
}
void PPM::saveToFile(ofstream& file) const {
    size_t height = redMatrix.getHeight();
    size_t width = redMatrix.getWidth();
    file << "P3" << endl;
    file << width << " " << height << endl;
    file << white << endl;
    for(size_t i = 0; i < height; i++)
        for(size_t j = 0; j < width; j++)
            file << redMatrix.getPixels()[i][j] << " " << greenMatrix.getPixels()[i][j] << " " << blueMatrix.getPixels()[i][j] << endl;
}