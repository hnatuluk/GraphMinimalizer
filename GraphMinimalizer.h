/* 
 * File:   GraphMinimalizer.h
 * Author: prcek
 *
 * Created on 8. duben 2012, 14:45
 */

#ifndef GRAPHMINIMALIZER_H
#define	GRAPHMINIMALIZER_H
#define GRAPHLOADERSSIZE 4
#define FINITESTATE 3
#define INPUT 1
#define STATE 2
#define INPUTSSTATETABLE 0
#include "File.h"
#include "GraphLoader.h"
#include "Exception.h"
#include "GraphChecker.h"
#include "GraphSolver.h"
#include "OutputWriter.h"

class GraphMinimalizerException : public Exception {
    string message;
public:
    GraphMinimalizerException(string m);
    string const &getMessage();
};

class GraphMinimalizer  {
    File f;
    GraphLoader **loaders;
    GraphChecker **checker;
    GraphSolver **solvers;
    OutputWriter *wr;
    void fillLoaders(const string &token, File &file) throw (GraphMinimalizerException);
    void loadGraph()throw (FileCannotBeOpenException);
    void checkGraph() throw (GraphMinimalizerException);
    void minimalizeGraph();
    void init();
public:
    GraphMinimalizer(File *f);
    GraphMinimalizer(File f);
    virtual ~GraphMinimalizer();
    void setOutputWrites(OutputWriter *owr);
    void minimalize() throw (FileCannotBeOpenException, GraphMinimalizerException);
    virtual const string &getName(const int &index);
};

#endif	/* GRAPHMINIMALIZER_H */

