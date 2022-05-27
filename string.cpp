#include <iostream>
#include <cstring>
#include <fstream>
#include "string.h"
using namespace std;

void String::copyFrom(const String& otherStr) {
    str = new char[strlen(otherStr.str) + 1];
    strcpy(str, otherStr.str);
}

void String::free() {
    delete[] str;
}

const char* String::getStr() const {
    return str;
}
void String::setStr(const char* otherStr) {
    delete[] str;
    str = new char[strlen(otherStr) + 1];
    strcpy(str, otherStr);
}

String::String() : String(""){
}
String::String(const char* str) {
    this->str = nullptr;
    setStr(str);
}
String::String(const String& otherStr) {
    copyFrom(otherStr);
}
String& String::operator=(const String& otherStr) {
    if(this != &otherStr)
    {
        free();
        copyFrom(otherStr);
    }
    return *this;
}
String::~String() {
    free();
}

const char& String::operator[](size_t index) const {
    if(index < 0 || index >= strlen(str))
        throw "Invalid index!";

    return str[index];
}

char& String::operator[](size_t index) {
    if(index < 0 || index >= strlen(str))
        throw "Invalid index!";

    return str[index];
}

void String::readFromFile(ifstream& file) {
    size_t length = 0;
    file.read((char*)&length, sizeof(size_t));
    char* str = new char[length];
    file.read((char*) str, sizeof(char) * length);
    setStr(str);
    delete[] str;
}
void String::saveToFile(ofstream& file) const {
    size_t length = strlen(str) + 1;
    file.write((const char*)&length, sizeof(size_t));
    file.write((const char*)str, sizeof(char) * length);
}

size_t String::length() const {
    return strlen(str);
}

istream& operator>>(istream& stream, String& str) {
    char* buffer = new char[1024];
    stream >> buffer;
    str.setStr(buffer);
    return stream;
}
ostream& operator<<(ostream& stream, const String& str) {
    stream << str.getStr();
    return stream;
}