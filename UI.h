#ifndef _UI
#define _UI
#include "session.h"

class UI {
    Session sessions[32];
    size_t sessionCount = 0;
    size_t currentSessionIndex = 0;

    void switchSessions(size_t);
    void open(const String&);
    void add(const String&);
    void close();
    void save();
    void sessionInfo();
    void allSessionsInfo();
    void grayscale();
    void monochrome();
    void negative();
    void rotate(bool);
    void help() const;
    void exitProgram() const;
public:
    void start();

    UI();
    UI(const UI&) = delete;
    UI& operator=(const UI&) = delete;
};
#endif