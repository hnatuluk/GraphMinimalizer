#include "InputLoader.h"

InputLoader::InputLoader() {
    filled = false;
}

InputLoader::~InputLoader() {
}

void InputLoader::readToken(File& file) {
    if (!filled) {
        int numberOfTokens;
        string token;
        file >> numberOfTokens;

        for (int i = 0; i < numberOfTokens; i++) {
            file >> token;
            if (check.count(token) == 0) {
                this->inputs.push_back(token);
                this->check.insert(token);
            }
        }
        filled = true;
    }


}

bool InputLoader::containsToken(const string& token)const {
    return check.count(token) != 0;
}

bool InputLoader::checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable) {
    return true;
}

int InputLoader::getSize()const {
    return check.size();
}

bool InputLoader::isFilled() const{
    return filled;
}

int InputLoader::getSizeOfAllValues() const{
    return getSize();
}

string* InputLoader::getAllValues() const{
    string *ret = new string[getSizeOfAllValues()];
    set<string>::iterator it;
    int i = 0;
    for (it = check.begin(); it != check.end(); it++){
        ret[i++] = (*it);
    }
    return ret;
}

string* InputLoader::getValuesFor(const string &s) const{
    return NULL;
}

bool InputLoader::containsValue(const string& s) const{
    return containsToken(s);
}
