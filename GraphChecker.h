/* 
 * File:   GraphChecker.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 13:51
 */

#ifndef GRAPHCHECKER_H
#define	GRAPHCHECKER_H
#include <string>
using namespace std;
class GraphChecker{
public:
    virtual ~GraphChecker(){}
    virtual bool containsToken(const string &token) const =0;
    virtual bool checkContent(const GraphChecker &states,const GraphChecker &inputs,const GraphChecker &finiteStates, const GraphChecker &inputStateTable)=0;
    virtual int getSize() const =0;
    virtual bool isFilled() const =0;
};

#endif	/* GRAPHCHECKER_H */

