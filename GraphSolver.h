/* 
 * File:   GraphSolver.h
 * Author: prcek
 *
 * Created on 9. duben 2012, 19:16
 */

#ifndef GRAPHSOLVER_H
#define	GRAPHSOLVER_H

#include <string>
using namespace std;

class GraphSolver {
public:
    virtual ~GraphSolver(){};
    virtual string* getAllValues() const = 0;
    virtual int getSizeOfAllValues() const = 0;
    virtual string* getValuesFor(const string &s) const = 0;
    virtual bool containsValue(const string &s) const = 0;
};

#endif	/* GRAPHSOLVER_H */

