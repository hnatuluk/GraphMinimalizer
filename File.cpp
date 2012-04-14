
#include "File.h"
#include <string>

File::File(void) {
    this->set = false;
}

File::File(string filename) {
    this->filename = filename;
    this->set = true;
}

File::~File(){}

bool File::openFile(void) {
    fileIs.open(filename.c_str(), ifstream::in);
    return fileIs.is_open() && fileIs.good();
}

bool File::closeFile(void) {
    if (this->open && fileIs.good()) {
        fileIs.close();
        return !fileIs.is_open();
    }
    return this->open;
}

bool File::eof(){
    return fileIs.eof();
}

void File::setFileName(string filename){
    this->filename=filename;
}

string File::getFileName(){
    return this->filename;
}

string File::getLine(){
    string command;
    getline(fileIs,command);
    return command;
}

File &File::operator >>(string& node){
    fileIs >> node;
    return *this;
}

File &File::operator >>(int& num){
    fileIs >> num;
    return *this;
}

File &File::operator =(const File& f){
    this->filename = f.filename;
    this->open = false;
    this->set = false;
    return *this;
}

FileCannotBeOpenException::FileCannotBeOpenException(string m){
    this->message = m;
}

FileCannotBeOpenException::~FileCannotBeOpenException(){}

const string & FileCannotBeOpenException::getMessage(){
    return this->message;
}