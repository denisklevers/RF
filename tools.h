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
#include <string>
#include <cstdlib>

// Data structs
struct intint 
{
    int A;
    int B;
};

struct IndexedData
{
    double** data;
    int rows;
    int cols;

    int keyCol;
    hashmap<intint> index;
    
    // ToDo: get column. get column in range ... get row (copy) ...
};

template <typename T> struct arr
{
    T* data;
    int size;
    
    T &operator[](int i) {
        if(i < size) {
            return data[i];
        } 
        
        throw std::out_of_range("arr::access - Index out of range");
    }
    
    std::string toString() {
        std::string s = "[ ";
        
        for(int i = 0; i < size; i++) {
            s += std::to_string(data[i])+" ";
        }
        
        return s+"]";
    }
};


// Array tools
double** createDoubleArray2D(int Nr, int Nc);
void     freeDoubleArray2D(double** A, int Nr);

template<typename T> arr<T> add(arr<T> A1, arr<T> A2) {
   
    arr<T> A;
    arr<T> ret = (A1.size > A2.size) ? (A = A2, copy(A1)) : (A = A1, copy(A2));
    
    for(int i = 0; i < A.size; i++) {
        ret.data[i] += A.data[i];
    }
    
    return ret;
}

template<typename T> arr<T> d_p(arr<T> A, int lag) {
    //...
    
    return NULL;
}


template<typename T> arr<T> copy(arr<T> A) {
    T* newA = new T[A.size]; 
   
    std::copy(A.data, A.data+A.size, newA);
        
    arr<T> RA = {newA, A.size};
    
    return RA;
}



// .CSV tools
void        loadCSV(const char *filename, double** M, int Nr, int Nc, int startPos);
IndexedData loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol);


// Probability tools
class coinFlipper {
public:
    coinFlipper();
    coinFlipper(double bias);
    bool coinFlip();
    
private:
    
    std::mt19937 rng;
    
    double p;
};


#endif /* TOOLS_H */

