/* 
 * File:   ConsoleWriter.h
 * Author: prcek
 *
 * Created on 14. duben 2012, 17:52
 */

#ifndef CONSOLEWRITER_H
#define	CONSOLEWRITER_H
#include "OutputWriter.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

class ConsoleWriter : public OutputWriter{
private:
    void writeStates(const string &statesName);
    void writeFinalStates(const string &finalStatesName);
    void writeInputsTable(const string &inputsTableName);
    void writeInputs(const string& inputsName);
protected:
    vector<string> states;
    vector<string> finalStates;
    vector<string> inputs;
    map<const string, const string*> inputsTable;
    int inputsLen;
public:
    ConsoleWriter();
    virtual ~ConsoleWriter();
    virtual void addState(const string &i, const bool &final);
    virtual void addInputStateTable(const string key,const string* i, const int length);
    virtual void addInput(const string &i);
    virtual void flush(const string& statesName, const string& inputsName, const string& inputsTableName, const string& finalStatesName)throw (Exception);
};

#endif	/* CONSOLEWRITER_H */

