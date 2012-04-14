/* 
 * File:   InputLoader.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 13:19
 */

#ifndef INPUTLOADER_H
#define	INPUTLOADER_H

#include "GraphLoader.h"
#include "GraphChecker.h"
#include "GraphSolver.h"
#include "File.h"
#include <vector>
#include <string>
#include <set>
using namespace std;
class InputLoader : public GraphLoader, public GraphChecker, public GraphSolver{
    vector<string> inputs;
    set<string> check;
    bool filled;
public:
    InputLoader();
    virtual ~InputLoader();
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


#endif	/* INPUTLOADER_H */

