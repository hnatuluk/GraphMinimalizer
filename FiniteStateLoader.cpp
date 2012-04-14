#include "FiniteStateLoader.h"
#include "File.h"
#include <iostream>
using namespace std;
FiniteStateLoader::FiniteStateLoader() {
}

FiniteStateLoader::~FiniteStateLoader() {
}

void FiniteStateLoader::readToken(File& file) {
    if (!filled) {
        int numberOfTokens;
        string token;
        file >> numberOfTokens;

        for (int i = 0; i < numberOfTokens; i++) {
            file >> token;
            this->states.insert(token);
        }
        filled = true;
    }
}

bool FiniteStateLoader::containsToken(const string& token) const {
    return this->states.count(token) != 0;
}

bool FiniteStateLoader::checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable) {
    set<string>::iterator it;
    bool ret = true;
    bool tmpRet;
    string value;
    for(it = this->states.begin(); it != this->states.end(); it++){
        value = (*it);
        tmpRet = states.containsToken(value);
        if(!tmpRet){
            cerr << "Finite state "+value+" is not in states..."<<endl;
            ret = false;
        }
    }
    return ret;
}

int FiniteStateLoader::getSize()const {
    return states.size();
}

bool FiniteStateLoader::isFilled() const{
    return filled;
}

int FiniteStateLoader::getSizeOfAllValues() const{
    return states.size();
}

string* FiniteStateLoader::getAllValues() const{
    string *ret = new string[getSizeOfAllValues()];
    set<string>::iterator it;
    int i = 0;
    for (it = states.begin(); it != states.end(); it++){
        ret[i++] = (*it);
    }
    return ret;
}

string* FiniteStateLoader::getValuesFor(const string &s) const{
    return NULL;
}

bool FiniteStateLoader::containsValue(const string& s) const{
    return containsToken(s);
}