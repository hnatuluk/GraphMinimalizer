/* 
 * File:   FiniteStateLoader.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 14:35
 */

#ifndef FINITESTATELOADER_H
#define	FINITESTATELOADER_H

#include "GraphLoader.h"
#include "GraphChecker.h"
#include "GraphSolver.h"
#include <set>
#include <string>
using namespace std;

class FiniteStateLoader : public GraphLoader, public GraphChecker, public GraphSolver{
    set<string> states;
    bool filled;
public:
    FiniteStateLoader();
    virtual ~FiniteStateLoader();
    virtual void readToken(File & file);
    virtual bool containsToken(const string &token)const;
    virtual bool checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable);
    virtual int getSize()const;
    virtual bool isFilled() const ;
    virtual string* getAllValues() const ;
    virtual string * getValuesFor(const string &s) const;
    virtual int getSizeOfAllValues() const;
    virtual bool containsValue(const string &s) const;
};

#endif	/* FINITESTATELOADER_H */

