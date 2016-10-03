/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tools.h
 *
 * Created on September 28, 2016, 9:13 PM
 */

#ifndef TOOLS_H
#define TOOLS_H

#include "hashmap.h"

// Structs
struct IndexedData{
    double** data;
    int keyCol;
    hashmap<int> index;
};

// Array tools
double** createDoubleArray2D(int Nr, int Nc);
void     freeDoubleArray2D(double** A, int Nr);

// .CSV tools
void        loadCSV(const char *filename, double** M, int Nr, int Nc, int startPos);
IndexedData loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol);


#endif /* TOOLS_H */

