#ifndef _SESSION
#define _SESSION
#include "photo.h"
#include "PBM.h"
#include "PGM.h"
#include "PPM.h"

class Session {
    static size_t nextId;
    size_t id;
    Photo** photos;
    size_t photoCount;

    void copyFrom(const Session&);
    void free();
public:
    Session();
    Session(const Photo**, size_t);
    Session(const Session&);
    Session& operator=(const Session&);
    ~Session();

    void add(const Photo&);
    void rotate(bool);
    void negative();
    void monochrome();
    void grayscale();
    void sessionInfo() const;
    const Photo& getPhotoByName(const String& name) const;
    void collage(bool, const String&, const String&, const String&);

    void save();
    //void saveAs(const String&) const; // I don't have any idea how to implement or where to implement it because it doesn't make ANY sense
    //void load(const String&); //its functionality is the same as open so doesn't make sense either
};
#endif