/* 
 * File:   main.cpp
 * Author: prcek
 *
 * Created on 8. duben 2012, 12:35
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "File.h"
#include "GraphMinimalizer.h"
#include "ConsoleWriter.h"
#include "FileWriter.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc < 2 || argc > 3){
        cerr << "Pocet vstupnich argumentů musí být roven 1 pro výstup na konsoli."<<endl;
        cerr << "Pocet vstupnich argumentů musí být roven 2 pro výstup na do souboru."<<endl;
        return 1;
    }
    OutputWriter *ow;
    if(argc == 2){
        ow = new ConsoleWriter();
    }else{
        ow = new FileWriter(argv[2]);
    }
    string input = argv[1];
    File *f = new File(input);
    GraphMinimalizer *g = new GraphMinimalizer(f);
    g->setOutputWrites(ow);
    g->minimalize();
    delete ow;
    delete g;
    delete f;
    return 0;
}

