


#include "FileWriter.h"
#include "File.h"
FileWriter::FileWriter(const string& filename){
    this->filename = filename;
}

FileWriter::~FileWriter(){}

void FileWriter::flush(const string& statesName, const string& inputsName, const string& inputsTableName, const string& finalStatesName)throw (Exception) {

    fileOs.open(filename.c_str(), ifstream::out);
    if (!(fileOs.is_open() && fileOs.good())){
        cerr << "File "<< filename << "cannot be open..."<<endl;
        throw new FileCannotBeOpenException("File "+ filename + "cannot be open...");
    }

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

    fileOs.close();
}

void FileWriter::writeInputs(const string& inputsName) {
    fileOs << inputsName << endl;
    fileOs << inputs.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = inputs.begin(); it != inputs.end(); it++) {
        if (whiteSpace) {
            fileOs << " " << (*it);
        } else {
            fileOs << (*it);
            whiteSpace = true;
        }
    }
    fileOs << endl;
}

void FileWriter::writeStates(const string &statesName) {
    fileOs << statesName << endl;
    fileOs << states.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = states.begin(); it != states.end(); it++) {
        if (whiteSpace) {
            fileOs << " " << (*it);
        } else {
            fileOs << (*it);
            whiteSpace = true;
        }
    }
    fileOs << endl;
}

void FileWriter::writeFinalStates(const string &finalStatesName) {
    fileOs << finalStatesName << endl;
    fileOs << finalStates.size() << endl;
    bool whiteSpace = false;
    for (vector<string>::const_iterator it = finalStates.begin(); it != finalStates.end(); it++) {
        if (whiteSpace) {
            fileOs << " " << (*it);
        } else {
            fileOs << (*it);
            whiteSpace = true;
        }
    }
    fileOs << endl;
}

void FileWriter::writeInputsTable(const string &inputsTableName) {
    fileOs << inputsTableName << endl;
    fileOs << inputsTable.size() << endl;
    fileOs << inputsLen << endl;
    for (map<const string, const string*>::const_iterator it = inputsTable.begin(); it != inputsTable.end(); it++) {
        const string key = (*it).first;
        const string* tmpInputsTable = (*it).second;
        fileOs << key;
        for (int i = 0; i < inputsLen; i++) {
            fileOs << " " << tmpInputsTable[i];
        }
        fileOs << endl;
    }
}