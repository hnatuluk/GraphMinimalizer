/* 
 * File:   File.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 12:39
 */




#ifndef FILE_H
#define	FILE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Exception.h"
using namespace std;
class File{
private:
    string filename;
    bool set;
    bool open;
    fstream fileIs;
public:
    File(void);
    File(string filename);
    virtual ~File(void);
    void setFileName(string filename);
    string getFileName(void);
    bool openFile(void);
    bool closeFile(void);
    bool eof(void);
    string getLine();
    File &operator>>(string &node);
    File &operator>>(int &num);
    File &operator=(const File &f);
};

class FileCannotBeOpenException : public Exception{
private:
    string message;
public:
    FileCannotBeOpenException(string m);
    virtual ~FileCannotBeOpenException(void);
    const string &getMessage();
};

#endif	/* FILE_H */

