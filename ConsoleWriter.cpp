#include "ConsoleWriter.h"

ConsoleWriter::ConsoleWriter() {
}

ConsoleWriter::~ConsoleWriter() {
    for (map<const string, const string*>::iterator it = inputsTable.begin();it != inputsTable.end();it++){
        const string* val = (*it).second;
        delete [] val;        
    }
}

void ConsoleWriter::addState(const string &i, const bool &final) {
    states.push_back(i);
    if (final) {
        finalStates.push_back(i);
    }
}

void ConsoleWriter::addInput(const string& i) {
    inputs.push_back(i);
}

void ConsoleWriter::addInputStateTable(const string key, const string* i, const int length) {
    inputsTable.insert(pair<const string, const string* > (key, i));
    inputsLen = length;
}

void ConsoleWriter::flush(const string& statesName, const string& inputsName, const string& inputsTableName, const string& finalStatesName)throw (Exception) {

    if (states.size() > 0) {
        writeStates(statesName);
    }
    if (finalStates.size() > 0) {
        writeFinalStates(finalStatesName);
    }
    if (inputs.size() > 0) {
        writeInputs(inputsName);
    }
    if (inputsTable.size() > 0) {
        writeInputsTable(inputsTableName);
    }
}

void ConsoleWriter::writeInputs(const string& inputsName) {
    cout << inputsName << endl;
    cout << inputs.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = inputs.begin(); it != inputs.end(); it++) {
        if (whiteSpace) {
            cout << " " << (*it);
        } else {
            cout << (*it);
            whiteSpace = true;
        }
    }
    cout << endl;
}

void ConsoleWriter::writeStates(const string &statesName) {
    cout << statesName << endl;
    cout << states.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = states.begin(); it != states.end(); it++) {
        if (whiteSpace) {
            cout << " " << (*it);
        } else {
            cout << (*it);
            whiteSpace = true;
        }
    }
    cout << endl;
}

void ConsoleWriter::writeFinalStates(const string &finalStatesName) {
    cout << finalStatesName << endl;
    cout << finalStates.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = finalStates.begin(); it != finalStates.end(); it++) {
        if (whiteSpace) {
            cout << " " << (*it);
        } else {
            cout << (*it);
            whiteSpace = true;
        }
    }
    cout << endl;
}

void ConsoleWriter::writeInputsTable(const string &inputsTableName) {
    cout << inputsTableName << endl;
    cout << inputsTable.size() << endl;
    cout << inputsLen << endl;
    for (map<const string, const string*>::const_iterator it = inputsTable.begin(); it != inputsTable.end(); it++) {
        const string key = (*it).first;
        const string* tmpInputsTable = (*it).second;
        cout << key;
        for (int i = 0; i < inputsLen; i++) {
            cout << " " << tmpInputsTable[i];
        }
        cout << endl;
    }
}
