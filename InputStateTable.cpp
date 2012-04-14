#include "InputStateTable.h"
#include "StateLoader.h"
#include <iostream>
using namespace std;
InputStateTable::InputStateTable() {
    filled = false;
}

InputStateTable::~InputStateTable() {
    map<string, string*>::iterator it;
    for (it = this->table.begin(); it != this->table.end(); it++) {
        string * s = (*it).second;
        delete [] s;
    }
}

int InputStateTable::getSize()const {
    return inputs*states;
}

bool InputStateTable::containsToken(const string& token)const {
    return table.find(token) != table.end();
}

bool InputStateTable::checkContent(const GraphChecker &states, const GraphChecker &inputs, const GraphChecker &finiteStates, const GraphChecker &inputStateTable) {
    map<string, string*>::iterator it;
    string key;
    string *values;
    bool ret = true;
    bool tmpRet;
    for (it = table.begin(); it != table.end(); it++) {
        key = (*it).first;
        values = (*it).second;
        tmpRet = states.containsToken(key);
        if (!tmpRet) {
            cerr << "The state " + key + "in InputStateTable is not in States set ..." << endl;
            ret = false;
        }
        for (int i = 0; i < this->states; i++) {
            tmpRet = states.containsToken(values[i]);
            if (!tmpRet && !(values[i]=="-")) {
                cerr << "The state " + values[i] + " in InputStateTable is not in States set ..." << endl;
                ret = false;
            }
        }
    }
    if (this->inputs != inputs.getSize()){
        cerr << "The inputs count defined in InputStateTable (" << this->inputs << ") does not correspond with Inputs(" << inputs.getSize() << ")" << endl ;
        ret = false;
    }
    if (this->states != states.getSize()){
        cerr << "The states count defined in InputStateTable (" << this->inputs << ") does not correspond with States(" << states.getSize() << ")" << endl ;
        ret = false;
    }
    return ret;
}

void InputStateTable::readToken(File& file) {
    if (!filled) {

        file >> states;
        file >> inputs;
        for (int x = 0; x < states; x++) {
            string key;
            string *values = new string[inputs];
            file >> key;
            for (int y = 0; y < inputs; y++) {
                string value;
                file >> value;
                values[y] = value;
            }
            table.insert(pair<string, string* > (key, values));
        }
        filled = true;
    }
}

bool InputStateTable::isFilled() const{
    return filled;
}

int InputStateTable::getSizeOfAllValues() const{
    return table.size();
}

string* InputStateTable::getAllValues() const{
    string *ret = new string[getSizeOfAllValues()];
    map<string, string*>::const_iterator it;
    string s;
    int i = 0;
    for (it = table.begin(); it != table.end(); it++){
        s = (*it).first;
        ret[i++] = s;
    }
    return ret;
}

string* InputStateTable::getValuesFor(const string &s) const{
    map<string, string*>::const_iterator it;
    string *ret;
    it = table.find(s);
    ret = (*it).second;
    if (it == table.end()){
        return NULL;
    }else{
        string *retA = new string[inputs];
        for (int i = 0; i < inputs; i++ ){
            retA[i] = ret[i];
        }
        return retA;
    }
}

bool InputStateTable::containsValue(const string& s) const{
    return containsToken(s);
}