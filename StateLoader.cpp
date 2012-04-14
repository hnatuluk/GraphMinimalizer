#include "StateLoader.h"
#include "File.h"

StateLoader::StateLoader() {
}

StateLoader::~StateLoader() {
}

void StateLoader::readToken(File& file) {
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

bool StateLoader::containsToken(const string &token) const{
    return this->states.count(token) != 0;
}

bool StateLoader::checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable) {
    return true;
}

int StateLoader::getSize()const {
    return states.size();
}

bool StateLoader::isFilled() const{
    return filled;
}

int StateLoader::getSizeOfAllValues() const{
    return states.size();
}

string* StateLoader::getAllValues() const{
    string *ret = new string[getSizeOfAllValues()];
    set<string>::iterator it;
    int i = 0;
    for (it = states.begin(); it != states.end(); it++){
        ret[i++] = (*it);
    }
    return ret;
}

string* StateLoader::getValuesFor(const string &s) const{
    return NULL;
}

bool StateLoader::containsValue(const string& s) const{
    return containsToken(s);
}
