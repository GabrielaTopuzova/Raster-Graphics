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

bool String::operator==(const String& other) const {
    return !strcmp(str, other.str);
}
bool String::operator!=(const String& other) const {
    return strcmp(str, other.str);
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

bool String::startsWith(const String& other) const {
    if(other.length() > this->length())
        return false;

    for(size_t i = 0; i < other.length(); i++)
        if(str[i] != other.str[i])
            return false;

    return true;
}

bool String::endsWith(const String& other) const {
    if(other.length() > this->length())
        return false;

    for(size_t i = 0; i < other.length(); i++)
        if(str[this->length() - 1 - i] != other.str[other.length() - 1 - i])
            return false;

    return true;
}

size_t String::indexOfInterval(size_t num) const {
    size_t count = 0;
    for(size_t i = 0; i < this->length(); i++) {
        if(str[i] == ' ') {
            count++;
        }
        if(count == num)
            return i;
    }
    return 0;
}

String String::substring(size_t from, size_t to) const {
    if(from > to || to >= length())
        return "";
    char* res = new char[to - from + 2];
    for(size_t i = 0; i < to - from + 1; i++)
        res[i] = str[from + i];
    res[to - from + 1] = '\0';
    String result = res;
    delete[] res;
    return result;
}
