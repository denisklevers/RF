/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analyzer.cpp
 * Author: Dan
 * 
 * Created on October 15, 2016, 10:39 PM
 */

#include "analyzer.h"
#include "arr.h"
#include "tools.h"
#include <iostream>

using namespace std;

analyzer::analyzer(IndexedData* Data) {
    data = Data;
}

/*
 * Applies the function func: M -> double onto the Data matrix of each day and 
 * takes the mean of the output
 */
doubledouble analyzer::averageAll(std::function<double(const arr2D<double>)> func) {
    
    // Reset iterator
    data->index.resetIterator();
 
    arr<double> rets {new double[data->index.size()], data->index.size()};
    
    // Loop over all days
    intint* val;
    int c = 0;
    while((val = data->index.next())!=NULL) {
   
        arr2D<double> A = data->getSubMatrixAsView(val->A,0, val->B, data->cols);
    
        rets[c] = func(A);
        
        c++;
    }
 
    return tools::mean(rets);
}
