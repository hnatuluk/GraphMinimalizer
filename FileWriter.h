/* 
 * File:   FileWriter.h
 * Author: prcek
 *
 * Created on 14. duben 2012, 18:08
 */

#ifndef FILEWRITER_H
#define	FILEWRITER_H
#include <iostream>
#include <fstream>
#include <sstream>

#include "ConsoleWriter.h"
#include "File.h"

class FileWriter : public ConsoleWriter {
    string filename;
    fstream fileOs;
    void writeStates(const string &statesName);
    void writeFinalStates(const string &finalStatesName);
    void writeInputsTable(const string &inputsTableName);
    void writeInputs(const string& inputsName);
public:
    FileWriter(const string &filename);
    virtual ~FileWriter();
    virtual void flush(const string& statesName, const string& inputsName, const string& inputsTableName, const string& finalStatesName)throw (Exception);
};

class FileWriterException : public Exception{
    const string message;
public:
    FileWriterException(const string message);
    virtual ~FileWriterException(void);
    virtual string const &getMessage(void);
};


#endif	/* FILEWRITER_H */

