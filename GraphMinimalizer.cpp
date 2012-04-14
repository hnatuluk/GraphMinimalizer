
#include "GraphMinimalizer.h"
#include "StateLoader.h"
#include "InputLoader.h"
#include "FiniteStateLoader.h"
#include "GraphLoader.h"
#include "InputStateTable.h"
#include <iostream>
using namespace std;

GraphMinimalizer::GraphMinimalizer(File *f) {
    init();
    this->f = *f;
}

GraphMinimalizer::GraphMinimalizer(File f) {
    init();
    this->f = f;
}

void GraphMinimalizer::init(){
    this->loaders = new GraphLoader*[GRAPHLOADERSSIZE];
    this->checker = new GraphChecker*[GRAPHLOADERSSIZE];
    this->solvers = new GraphSolver*[GRAPHLOADERSSIZE];
    FiniteStateLoader * fsl = new FiniteStateLoader();
    InputLoader * il = new InputLoader();
    StateLoader * sl = new StateLoader();
    InputStateTable * ist = new InputStateTable();
    loaders[FINITESTATE] = fsl;
    checker[FINITESTATE] = fsl;
    solvers[FINITESTATE] = fsl;
    loaders[INPUT] = il;
    checker[INPUT] = il;
    solvers[INPUT] = il;
    loaders[STATE] = sl;
    checker[STATE] = sl;
    solvers[STATE] = sl;
    loaders[INPUTSSTATETABLE] = ist;
    checker[INPUTSSTATETABLE] = ist;
    solvers[INPUTSSTATETABLE] = ist;
}

GraphMinimalizer::~GraphMinimalizer() {
    for (int i = 0; i < GRAPHLOADERSSIZE; i++) {
        delete loaders[i];
    }
    delete [] loaders;
    //Delete prvky z checkers ne, protoze jsou totozne
    //s temi, co jsou v loaders.
    delete [] checker;
    delete [] solvers;
}

void GraphMinimalizer::fillLoaders(const string& token, File& file) throw (GraphMinimalizerException) {
    bool read = false;
    for (int i = 0; i < GRAPHLOADERSSIZE; i++) {
        if (token == getName(i)) {
            loaders[i]->readToken(file);
            read = true;
            break;
        }
    }
    if (!read) {
        cerr << "Unknown token name " + token << endl;
        throw new GraphMinimalizerException("Unknown token name " + token);
    }
}

void GraphMinimalizer::minimalize() throw (FileCannotBeOpenException, GraphMinimalizerException) {
    loadGraph();
    checkGraph();
    minimalizeGraph();
}

void GraphMinimalizer::minimalizeGraph(){
    int statesNo = solvers[STATE]->getSizeOfAllValues();
    int inputsNo = solvers[INPUT]->getSizeOfAllValues();
    int maxGroup = 0;
    string *states = solvers[STATE]->getAllValues();
    map<string, int> indexes;
    int* subGroups = new int [statesNo];
    string **inputStateTable = new string *[statesNo];
    int **statesTable = new int* [statesNo];
    int **statesTablePrev = new int* [statesNo];
    for (int i = 0 ; i< statesNo ; i++){
        statesTable[i] = new int [inputsNo];
        statesTablePrev[i] = new int [inputsNo];
    }

    for (int i = 0; i < statesNo ; i++){
        const string &key = states[i];
        int subGroup = solvers[FINITESTATE]->containsValue(key)?0:1;
        maxGroup = subGroup > maxGroup ?subGroup:maxGroup;
        indexes.insert(pair<string, int>(states[i],i));
        subGroups[i] = subGroup;
        inputStateTable[i] = solvers[INPUTSSTATETABLE]->getValuesFor(key);
    }
    delete [] states;
    states = NULL;

    delete [] subGroups;
    subGroups = NULL;
    for (int i = 0 ; i< statesNo ; i++){
        delete [] statesTable[i];
        delete [] statesTablePrev[i];
        delete [] inputStateTable[i];
        statesTable[i] = NULL;
        statesTablePrev[i] = NULL;
        inputStateTable[i] = NULL;
    }
    delete [] statesTable;
    statesTable = NULL;
    delete [] statesTablePrev;
    statesTablePrev = NULL;
    delete [] inputStateTable;
    inputStateTable = NULL;
}

void GraphMinimalizer::loadGraph() throw (FileCannotBeOpenException) {
    string token;
    bool open = f.openFile();
    if (open) {
        while (!f.eof()) {
            f >> token;
            fillLoaders(token, f);
        }
        f.closeFile();
    } else {
        cerr << "The file " + f.getFileName() + " cannot be open." << endl;
        throw new FileCannotBeOpenException("The file " + f.getFileName() + " cannot be open.");
    }
}

void GraphMinimalizer::checkGraph() throw (GraphMinimalizerException) {
    bool passed = true;
    const GraphChecker &states = (*checker[STATE]);
    const GraphChecker &inputs = (*checker[INPUT]);
    const GraphChecker &finiteStates = (*checker[FINITESTATE]);
    const GraphChecker &inputStateTable = (*checker[INPUTSSTATETABLE]);
    for (int i = 0; i < GRAPHLOADERSSIZE; i++) {
        bool tmpPassed = checker[i]->checkContent(states, inputs, finiteStates, inputStateTable);
        if (!tmpPassed) {
            passed = false;
        }
        tmpPassed = checker[i]->isFilled();
        if(!tmpPassed){
            cerr << "The " << getName(i) << " component is not filled. Check the file ..."<<endl;
        }
    }
    if (!passed) {
        cerr << "The graph is not build correctly" << endl;
        throw new GraphMinimalizerException("The graph is not build correctly");
    }
}

GraphMinimalizerException::GraphMinimalizerException(string m) {
    this->message = m;
}

string const &GraphMinimalizerException::getMessage() {
    return this->message;
}

const string &GraphMinimalizer::getName(const int& index) {
    static const string names[GRAPHLOADERSSIZE] = {"InputsStateTable", "Inputs", "States", "FiniteStates"};
    static const string noRet = "";
    if (index < GRAPHLOADERSSIZE) {
        return names[index];
    } else {
        return noRet;
    }
}