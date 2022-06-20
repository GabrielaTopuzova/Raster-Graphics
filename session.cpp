#include "session.h"
#include "PPM.h"
#include "PGM.h"
#include "PBM.h"

size_t Session::nextId = 0;

void Session::copyFrom(const Session& otherSession) {
    id = otherSession.id;

    photoCount = otherSession.photoCount;
    photos = new Photo*[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        photos[i] = otherSession.photos[i]->clone();
}
void Session::free() {
    for(size_t i = 0; i < photoCount; i++)
        delete photos[i];
    delete[] photos;
}

Session::Session() {
    id = nextId;
    nextId++;
    photos = nullptr;
    photoCount = 0;
}
Session::Session(const Photo** photos, size_t countP) {
    id = nextId;
    nextId++;

    photoCount = countP;
    this->photos = new Photo*[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        this->photos[i] = photos[i]->clone();
}
Session::Session(const Session& otherSession) {
    copyFrom(otherSession);
}
Session& Session::operator=(const Session& otherSession) {
    if(this != &otherSession) {
        free();
        copyFrom(otherSession);
    }
    return *this;
}
Session::~Session() {
    free();
}

void Session::add(const Photo& addition) {
    Photo** result = new Photo*[photoCount + 1];
    for(size_t i = 0; i < photoCount; i++)
        result[i] = photos[i];

    result[photoCount] = addition.clone();
    photoCount++;

    delete[] photos;
    photos = result;
}
void Session::sessionInfo() const {
    cout << "Session id: " << id << endl;

    cout << "Photos in session: " << endl;
    for(size_t i = 0; i < photoCount; i++)
        cout << photos[i]->getName() << endl;
}
const Photo& Session::getPhotoByName(const String& name) const {
    for (int i = 0; i < photoCount; i++)
        if (photos[i]->getName() == name)
            return *photos[i];
    throw "Photo does not exist!";
}
void Session::collage(bool direction, const String& photo1Name, const String& photo2Name, const String& resultPhoto) {
    const Photo& photo1 = getPhotoByName(photo1Name);
    const Photo& photo2 = getPhotoByName(photo2Name);
    if(photo1.getType() != photo2.getType()) 
        throw "Cannot make a collage from different types!";

    if(photo1.getPixels() != photo2.getPixels())
        throw "Cannot make a collage from photos with different size!";

    if(photo1.getWhite() != photo2.getWhite())
        throw "Cannot make a collage from photos with different max white value!";

    size_t resultHeight, resultWidth;
    size_t** resultMatrix;

    size_t** red;
    size_t** green;
    size_t** blue;

    if(direction && (photo1.getType() == 1 || photo1.getType() == 2)) {
        resultHeight = photo1.getHeight();
        resultWidth = photo1.getWidth() + photo2.getWidth();
        resultMatrix = new size_t*[resultHeight];

        for(size_t i = 0; i < resultHeight; i++) {
            resultMatrix[i] = new size_t[resultWidth];
            for(size_t j = 0; j < photo1.getWidth(); j++)
                resultMatrix[i][j] = photo1.getPixels().getPixels()[i][j];
        }

        for(size_t i = 0; i < resultHeight; i++)
            for(size_t j = 0; j < photo2.getWidth(); j++)
                resultMatrix[i][j + photo1.getWidth()] = photo2.getPixels().getPixels()[i][j];
        
    } else if(direction && photo1.getType() == 3) {
        resultHeight = photo1.getHeight();
        resultWidth = photo1.getWidth() + photo2.getWidth();
        red = new size_t*[resultHeight];
        green = new size_t*[resultHeight];++
        blue = new size_t*[resultHeight];

        for(size_t i = 0; i < resultHeight; i++) {
            red[i] = new size_t[resultWidth];
            green[i] = new size_t[resultWidth];
            blue[i] = new size_t[resultWidth];

            for(size_t j = 0; j < photo1.getWidth(); j++) {
                red[i][j] = photo1.getRed().getPixels()[i][j];
                green[i][j] = photo1.getGreen().getPixels()[i][j];
                blue[i][j] = photo1.getBlue().getPixels()[i][j];
            }
        }

        for(size_t i = 0; i < resultHeight; i++)
            for(size_t j = 0; j < photo2.getWidth(); j++) {
                red[i][j + photo1.getWidth()] = photo2.getRed().getPixels()[i][j];
                green[i][j + photo1.getWidth()] = photo2.getGreen().getPixels()[i][j];
                blue[i][j + photo1.getWidth()] = photo2.getBlue().getPixels()[i][j];
            }
        
    } else if(!direction && (photo1.getType() == 1 || photo1.getType() == 2)) {
        resultHeight = photo1.getHeight() + photo2.getHeight();
        resultWidth = photo1.getWidth();
        resultMatrix = new size_t*[resultHeight];

        for(size_t i = 0; i < photo1.getHeight(); i++) {
            resultMatrix[i] = new size_t[resultWidth];
            for(size_t j = 0; j < photo1.getWidth(); j++)
                resultMatrix[i][j] = photo1.getPixels().getPixels()[i][j];
        }

        for(size_t i = 0; i < photo2.getHeight(); i++) {
            resultMatrix[i + photo1.getHeight()] = new size_t[resultWidth];
            for(size_t j = 0; j < photo2.getWidth(); j++)
                resultMatrix[i + photo1.getHeight()][j] = photo2.getPixels().getPixels()[i][j];
        }
    } else if(!direction && photo1.getType() == 3) {

        resultHeight = photo1.getHeight() + photo2.getHeight();
        resultWidth = photo1.getWidth();
        red = new size_t*[resultHeight];
        green = new size_t*[resultHeight];
        blue = new size_t*[resultHeight];

        for(size_t i = 0; i < photo1.getHeight(); i++) {
            red[i] = new size_t[resultWidth];
            green[i] = new size_t[resultWidth];
            blue[i] = new size_t[resultWidth];

            for(size_t j = 0; j < photo1.getWidth(); j++) {
                red[i][j] = photo1.getRed().getPixels()[i][j];
                green[i][j] = photo1.getGreen().getPixels()[i][j];
                blue[i][j] = photo1.getBlue().getPixels()[i][j];
            }
        }

        for(size_t i = 0; i < photo2.getHeight(); i++) {
            red[i + photo1.getHeight()] = new size_t[resultWidth];
            green[i + photo1.getHeight()] = new size_t[resultWidth];
            blue[i + photo1.getHeight()] = new size_t[resultWidth];

            for(size_t j = 0; j < photo2.getWidth(); j++) {
                red[i + photo1.getHeight()][j] = photo2.getRed().getPixels()[i][j];
                green[i + photo1.getHeight()][j] = photo2.getGreen().getPixels()[i][j];
                blue[i + photo1.getHeight()][j] = photo2.getBlue().getPixels()[i][j];
            }
        }
    }
    switch (photo1.getType()) {
        case 1: {
            PixelMatrix result(resultMatrix, resultHeight, resultWidth);
            add(PBM(resultPhoto, result));
        }
            break;
        case 2: { 
            PixelMatrix result(resultMatrix, resultHeight, resultWidth);
            add(PGM(resultPhoto, result, photo1.getWhite()));
        }
            break;
        case 3: {
            PixelMatrix resRed(red, resultHeight, resultWidth);
            PixelMatrix resGreen(green, resultHeight, resultWidth);
            PixelMatrix resBlue(blue, resultHeight, resultWidth);
            add(PPM(resultPhoto, photo1.getWhite(), resRed, resGreen, resBlue));
        }
    }
}

void Session::save() {
    for(size_t i = 0; i < photoCount; i++)
        photos[i]->save();
}

void Session::rotate(bool direction) {
    for(size_t i = 0; i < photoCount; i++) {
        photos[i] = photos[i]->rotate(direction);
    }
}

void Session::negative() {
    for(size_t i = 0; i < photoCount; i++) {
        photos[i] = photos[i]->negative();
    }
}

void Session::monochrome() {
    for(size_t i = 0; i < photoCount; i++) {
        photos[i] = photos[i]->monochrome();
    }
}

void Session::grayscale() {
    for(size_t i = 0; i < photoCount; i++) {
        photos[i] = photos[i]->grayscale();
    }
}

size_t Session::getId() const {
    return id;
}