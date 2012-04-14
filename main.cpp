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
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    if (argc != 2){
        cerr << "Pocet vstupnich argumentů musí být roven 1."<<endl;
        return 1;
    }
    string s = argv[1];
    File *f = new File(s);
    GraphMinimalizer *g = new GraphMinimalizer(f);
    g->minimalize();
    delete g;
    delete f;
    return 0;
}

