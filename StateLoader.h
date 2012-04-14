/* 
 * File:   StateLoader.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 13:15
 */

#ifndef STATELOADER_H
#define	STATELOADER_H

#include "GraphLoader.h"
#include "File.h"
#include "GraphChecker.h"
#include "GraphSolver.h"
#include <set>
#include <string>
using namespace std;
class StateLoader : public GraphLoader, public GraphChecker, public GraphSolver{
    set<string> states;
    bool filled;
public:
    StateLoader();
    virtual ~StateLoader();
    virtual void readToken(File & file);
    virtual bool containsToken(const string &token) const;
    virtual bool checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable);
    virtual int getSize()const;
    virtual bool isFilled() const ;
    virtual string* getAllValues() const ;
    virtual string * getValuesFor(const string &s) const;
    virtual int getSizeOfAllValues() const;
    virtual bool containsValue(const string &s) const;
};

#endif	/* STATELOADER_H */

