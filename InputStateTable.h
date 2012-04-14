/* 
 * File:   InputStateTable.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 20:13
 */

#ifndef INPUTSTATETABLE_H
#define	INPUTSTATETABLE_H

#include "GraphLoader.h"
#include "GraphChecker.h"
#include "GraphSolver.h"
#include <map>

using namespace std;

class InputStateTable : public GraphLoader, public GraphChecker, public GraphSolver{
    map<string,string*> table;
    bool filled;
    int inputs;
    int states;
public:
    InputStateTable(void);
    virtual ~InputStateTable(void);
    virtual bool containsToken(const string& token)const;
    virtual void readToken(File& file);
    virtual bool checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable);
    virtual int getSize()const;
    virtual bool isFilled() const ;
    virtual string* getAllValues() const ;
    virtual string * getValuesFor(const string &s) const;
    virtual int getSizeOfAllValues() const;
    virtual bool containsValue(const string &s) const;
};

#endif	/* INPUTSTATETABLE_H */

