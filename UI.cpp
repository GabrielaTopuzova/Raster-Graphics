#include "UI.h"

UI::UI() {
    sessionCount = 0;
    currentSessionIndex = 0;
}

void UI::switchSessions(size_t next) {
    for(size_t i = 0; i < sessionCount; i++)
        if(sessions[i].getId() == next) {
            currentSessionIndex = i;
            cout<<"Successfuly switch of session"<<endl;
            return;
        }
    cout<<"Invalid session index"<<endl;
}

void UI::open(const String& initialFile) {
    sessions[sessionCount] = Session();
    if(initialFile.endsWith(".pbm"))
        sessions[sessionCount].add(PBM(initialFile));
    if(initialFile.endsWith(".pgm"))
        sessions[sessionCount].add(PGM(initialFile));
    if(initialFile.endsWith(".ppm"))
        sessions[sessionCount].add(PPM(initialFile));
    sessionCount++;
}
void UI::add(const String& name) {
    if(name.endsWith(".pbm"))
        sessions[currentSessionIndex].add(PBM(name));
    if(name.endsWith(".pgm"))
        sessions[currentSessionIndex].add(PGM(name));
    if(name.endsWith(".ppm"))
        sessions[currentSessionIndex].add(PPM(name));
}

void UI::close() {
    sessionCount--;
    for(size_t i = currentSessionIndex; i < sessionCount; i++)
        sessions[i] = sessions[i + 1];
    currentSessionIndex = min(sessionCount -1, currentSessionIndex);
}

void UI::exitProgram() const {
    exit(0);
}

void UI::save() {
    sessions[currentSessionIndex].save();
}

void UI::help() const {
    cout << "---------------------------------------------------------" << endl;
    cout << "The following commands are supported: " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "open <file>        opens <file>" << endl;
    cout << "close              closes currently opened session" << endl;
    cout << "save               saves the currently open session" << endl;
    cout << "help               prints this information" << endl;
    cout << "exit               exists the program" << endl;
    cout << "grayscale          edits photo making it black and white" << endl;
    cout << "monochrome         edits photo making the pixels only black or white" << endl;
    cout << "negative           reverses the colors in the photo" << endl;
    cout << "rotate <direction> rotates the photo right or left" << endl;
    cout << "save               makes the requested changes and saves the changed photos" << endl;
    cout << "session info       gives information about the current session" << endl;
    cout << "sessions info      gives information about all sessions" << endl;
    cout << "switch <id>        switches the current session with session N: id" << endl;
    cout << "---------------------------------------------------------" << endl;
}

void UI::start() {
    while (true) {
        try{
            cout<<">";

            char buffer[1024];
            cin.getline(buffer, 1024);
            String bufferStr = String(buffer);

            if(bufferStr.startsWith("exit")) {
                exitProgram();
            } else if(bufferStr.startsWith("close")) {
                if (sessionCount > 0) {
                    close();
                } else {
                    cout<<"There is no active session"<<endl;
                }
            } else if(bufferStr.startsWith("open ")) {
                open(bufferStr.getStr() + 5);
            } else if (bufferStr.startsWith("add ")) {
                if (sessionCount > 0) {
                    add(bufferStr.getStr() + 4);
                } else {
                    cout<<"There is no active session"<<endl;
                }
            } else if(bufferStr.startsWith("save")) {
                if (sessionCount > 0) {
                    save();
                } else {
                    cout<<"There is no active session"<<endl;
                }
            } else if(bufferStr.startsWith("session info")) {
                sessionInfo();
            } else if(bufferStr.startsWith("sessions info")) {
                allSessionsInfo();
            } else if(bufferStr.startsWith("help")) {
                help();
            } else if(bufferStr.startsWith("monochrome")) {
                monochrome();
            } else if(bufferStr.startsWith("grayscale")) {
                grayscale();
            } else if(bufferStr.startsWith("negative")) {
                negative();
            } else if(bufferStr.startsWith("rotate left")) {
                rotate(true);
            } else if(bufferStr.startsWith("rotate right")) {
                rotate(false);
            } else if(bufferStr.startsWith("collage horizontal")) {
                String photo1 = bufferStr.substring(bufferStr.indexOfInterval(2) + 1, bufferStr.indexOfInterval(3) - 1);
                String photo2 = bufferStr.substring(bufferStr.indexOfInterval(3) + 1, bufferStr.indexOfInterval(4) - 1);
                String photoRes = bufferStr.substring(bufferStr.indexOfInterval(4) + 1, bufferStr.length() - 1);
                sessions[currentSessionIndex].collage(true, photo1, photo2, photoRes);
            } else if(bufferStr.startsWith("collage vertical")) {
                String photo1 = bufferStr.substring(bufferStr.indexOfInterval(2) + 1, bufferStr.indexOfInterval(3) - 1);
                String photo2 = bufferStr.substring(bufferStr.indexOfInterval(3) + 1, bufferStr.indexOfInterval(4) - 1);
                String photoRes = bufferStr.substring(bufferStr.indexOfInterval(4) + 1, bufferStr.length() - 1);
                sessions[currentSessionIndex].collage(false, photo1, photo2, photoRes);
            } else if(bufferStr.startsWith("switch")) {
                String idStr = bufferStr.substring(bufferStr.indexOfInterval(1) + 1, bufferStr.length() - 1);
                size_t id = atoi(idStr.getStr());
                switchSessions(id);
            } else {
                cout << "No such command! Type help to see all supported commands!" << endl;
            }
        } catch(const char* error) {
            cout << error << endl;
        }
    }
}
void UI::sessionInfo() {
    if(sessionCount > 0) {
        sessions[currentSessionIndex].sessionInfo();
    }
    else {
        cout<<"There is no active session"<<endl;
    }
}
void UI::allSessionsInfo() {
    cout<<"There are "<<sessionCount<<" sessions:"<<endl;
    for(size_t i = 0; i < sessionCount; i++) {
        sessions[i].sessionInfo();
        cout<<endl;
    }
}

void UI::grayscale() {
    for(size_t i = 0; i < sessionCount; i++)
        sessions[i].grayscale();
}
void UI::monochrome() {
    for(size_t i = 0; i < sessionCount; i++)
        sessions[i].monochrome();
}
void UI::negative() {
    for(size_t i = 0; i < sessionCount; i++)
        sessions[i].negative();
}
void UI::rotate(bool direction) {
    for(size_t i = 0; i < sessionCount; i++)
        sessions[i].rotate(direction);
}