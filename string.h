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

    bool operator==(const String&) const;
    bool operator!=(const String&) const;

    const char& operator[](size_t) const;
    char& operator[](size_t);
    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, const String&);
    
    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    size_t length() const;
    bool startsWith(const String&) const;
    bool endsWith(const String&) const;
    size_t indexOfInterval(size_t) const;
    String substring(size_t, size_t) const;
}; 
#endif