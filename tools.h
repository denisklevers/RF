/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tools.h
 * Author: krefl
 *
 * Created on September 28, 2016, 9:13 PM
 */

#ifndef TOOLS_H
#define TOOLS_H

// Array tools
double** createDoubleArray(int Nr, int Nc);
void     freeDoubleArray(double** A, int Nr);

// .CSV tools
void     loadCSV(const char *filename, double** M, int Nr, int Nc, int startPos);


#endif /* TOOLS_H */

