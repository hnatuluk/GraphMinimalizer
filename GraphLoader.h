/* 
 * File:   GraphLoader.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 13:09
 */

#ifndef GRAPHLOADER_H
#define	GRAPHLOADER_H

#include "File.h"

class GraphLoader{
public:
    virtual ~GraphLoader(){};
    virtual void readToken(File & file)=0;
};


#endif	/* GRAPHLOADER_H */

