#ifndef __STRING
#define __STRING
#include <fstream>
using namespace std;

class String {
    char* str;

    void copyFrom(const String&);
    void free();
public:
    const char* getStr() const;
    void setStr(const char*);

    String();
    String(const char*);
    String(const String&);
    String& operator=(const String&);
    ~String();

    const char& operator[](size_t) const;
    char& operator[](size_t);
    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, const String&);
    
    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    size_t length() const;
};
#endif