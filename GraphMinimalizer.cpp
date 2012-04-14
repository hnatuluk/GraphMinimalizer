
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

void GraphMinimalizer::init() {
    this->wr = NULL;
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

void GraphMinimalizer::setOutputWrites(OutputWriter* owr){
    this->wr = owr;
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

void GraphMinimalizer::minimalizeGraph() {
    int statesNo = solvers[STATE]->getSizeOfAllValues();
    int inputsNo = solvers[INPUT]->getSizeOfAllValues();
    int maxGroup = 0;
    string *states = solvers[STATE]->getAllValues();
    map<string, int> indexes;
    int* subGroups = new int [statesNo + 1];
    string **inputStateTable = new string *[statesNo];
    int **statesTable = new int* [statesNo];
    for (int i = 0; i < statesNo; i++) {
        statesTable[i] = new int [inputsNo];
    }

    /*Inicializace blanku*/
    indexes.insert(pair<string, int>("-", statesNo));
    subGroups[statesNo] = -1;

    /*Inicializace prechodu*/
    for (int i = 0; i < statesNo; i++) {
        const string &key = states[i];
        int subGroup = solvers[FINITESTATE]->containsValue(key) ? 0 : 1;
        maxGroup = subGroup > maxGroup ? subGroup : maxGroup;
        indexes.insert(pair<string, int>(states[i], i));
        /*Posunuto kvuli blanku*/
        subGroups[i] = subGroup;
        inputStateTable[i] = solvers[INPUTSSTATETABLE]->getValuesFor(key);
    }
    delete [] states;
    states = NULL;
    bool everChange;
    do {
        everChange = false;
        /*Inicializace*/
        for (int x = 0; x < statesNo; x++) {
            for (int y = 0; y < inputsNo; y++) {
                string key = inputStateTable[x][y];
                int value = (*indexes.find(key)).second;
                int sValue = subGroups[value];
                statesTable[x][y] = sValue;
            }
        }
        /*Vypočet*/
        for (int x = 1; x < statesNo; x++) {
            for (int z = 0; z < x; z++) {
                if (subGroups[x] == subGroups[z]) {
                    for(int y = 0; y<inputsNo; y++){
                        if(statesTable[x][y] != statesTable[z][y]){
                            subGroups[x] = ++maxGroup;
                            everChange = true;
                            break;
                        }
                    }
                }
            }
        }
    } while (everChange);

    /*Naplneni vystupu*/
    string *inputs = solvers[INPUT]->getAllValues();
    for(int x = 0; x<solvers[INPUT]->getSizeOfAllValues();x++){
        this->wr->addInput(inputs[x]);
    }
    delete [] inputs;
    map<int,string>repre;

    bool *picked = new bool[statesNo];
    for (int x = 0; x < statesNo; x++){
        picked[x] = false;
    }

    /*Ulozim states a vyberu reprezentatny*/
    for(map<string,int>::const_iterator it = indexes.begin(); it != indexes.end();it++){
        string key = (*it).first;
        int index = (*it).second;
        int subGroup = subGroups[index];
        /*Blank preskocit*/
        if (subGroup < 0){
            continue;
        }
        if(!picked[subGroup]){
            picked[subGroup] = true;
            repre.insert(pair<int,string> (subGroup,key));
            this->wr->addState(key,checker[FINITESTATE]->containsToken(key));
        }
    }

    delete [] picked;

    for(map<int,string>::const_iterator it = repre.begin(); it != repre.end(); it ++){
        string key = (*it).second;
        string* tmpInputTable = solvers[INPUTSSTATETABLE]->getValuesFor(key);
        for (int i = 0 ; i < inputsNo ; i ++){
            int index = (*indexes.find(tmpInputTable[i])).second;
            map<int,string>::const_iterator tmpStringRepre = repre.find(subGroups[index]);
            /*Blank neni reprezentant, proto ten if*/
            if(tmpStringRepre != repre.end()){
                tmpInputTable[i] = (*tmpStringRepre).second;
            }
        }
        this->wr->addInputStateTable(key,tmpInputTable, inputsNo);
    }

    this->wr->flush(getName(STATE),getName(INPUT),getName(INPUTSSTATETABLE),getName(FINITESTATE));

    delete [] subGroups;
    subGroups = NULL;
    for (int i = 0; i < statesNo; i++) {
        delete [] statesTable[i];
        delete [] inputStateTable[i];
        statesTable[i] = NULL;
        inputStateTable[i] = NULL;
    }
    delete [] statesTable;
    statesTable = NULL;
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
        if (!tmpPassed) {
            cerr << "The " << getName(i) << " component is not filled. Check the file ..." << endl;
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