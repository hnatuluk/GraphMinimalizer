/* 
 * File:   Exception.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 19:20
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <string>
using namespace std;

class Exception{
public:
    virtual ~Exception(void){}
    virtual string const &getMessage()=0;
};

#endif	/* EXCEPTION_H */

