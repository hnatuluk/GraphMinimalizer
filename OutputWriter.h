/* 
 * File:   OutputWrite.h
 * Author: prcek
 *
 * Created on 14. duben 2012, 17:50
 */

#ifndef OUTPUTWRITE_H
#define	OUTPUTWRITE_H

#include <string>

#include "Exception.h"
using namespace std;

class OutputWriter{
public:
    virtual ~OutputWriter(){}
    virtual void addState(const string &i, const bool &final)=0;
    virtual void addInput(const string &i)=0;
    virtual void addInputStateTable(const string key,const string* i, const int length)=0;
    virtual void flush(const string& statesName, const string& inputsName, const string& inputsTableName, const string& finalStatesName) throw (Exception) =0;
};

#endif	/* OUTPUTWRITE_H */

