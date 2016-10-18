/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   analyzer.h
 * Author: krefl
 *
 * Created on October 15, 2016, 10:39 PM
 */

#ifndef ANALYZER_H
#define ANALYZER_H

#include "tools.h"


using namespace tools;

class analyzer {
public:
    analyzer(IndexedData* Data);
   
    doubledouble averageAll(std::function<double(arr2D<double>)> func);
    
private:
    IndexedData* data;
};

#endif /* ANALYZER_H */

