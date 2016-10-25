/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arr.h
 * Author: Dan
 *
 * Created on October 22, 2016, 8:09 PM
 */

#ifndef ARR_H
#define ARR_H

template <typename T> struct arr
{
    T* data;
    int length;
    
    T &operator[](int i) {
        if(i < length) {
            return data[i];
        } 
        
        throw std::out_of_range("arr::access - Index out of range");
    }
   
    int size(){
        return length;
    }
    
    void multiply(T C) {
        for(int i = 0; i < length; i++) {
            data[i] *= C;
        }
    }
    
    void divide(T C) {
        if(C!=0) {
            multiply(1/C);
        }
        
        throw std::overflow_error("arr::divide - Divide by zero");
    }
    
    void add(T C) {
        for(int i = 0; i < length; i++) {
            data[i] += C;
        }
    }
    
    void sub(T C) {
        for(int i = 0; i < length; i++) {
            data[i] -= C;
        }
    }
    
    void set(T C) {
        for(int i = 0; i < length; i++) {
            data[i] = C;
        }
    }
    
    /*
        Applies the supplied function  element-wise 
     *  f: <T> -> <T>
     */
    void apply(T (*function)(T)) {
        for(int i = 0; i < length; i++) {
            data[i] = function(data[i]);
        }
    }
    
    std::string toString() {
        std::string s = "L: "+std::to_string(length)+"\n[ ";
        
        for(int i = 0; i < length; i++) {
            s += std::to_string(data[i])+" ";
        }
        
        return s+"]";
    }
    
};


template <typename T> struct arr2D
{
    T** data;
    int Nr;
    int Nc;   
    
    int r = 0;
    int c = 0;
    
    arr2D() {}
    /*
     * Initalizes as view
     *
     */
    arr2D(int rs, int cs) {
        r = rs;
        c = cs;
    }
    
    
    /*
        Get column col
        [r1,r2)
     
     */
    arr<double> getCol(int col, int r1, int r2) 
    {
        
        if(col < Nc && r1 >= 0 && r2 <= Nr && r1 <= r2) 
        {
          
            // Prepare data
            double* A = new double[r2-r1];
            
            for(int i = r1; i < r2; i++) {
                A[i-r1] = data[r+i][c+col];
            }
       
            return {A, r2-r1};
        }
        
        throw std::out_of_range("arr2D::getCol - Invalid indices ("+std::to_string(col)+","+std::to_string(r1)+","+std::to_string(r2)+")");
    }
    
    arr<double> getCol(int col) 
    {
        return getCol(col, 0, Nr);
    }
    
    /*
     *  Applies the supplied function  element-wise 
     *  f: <T> -> <T>
     */
    void apply(T (*function)(T)) {
        for(int i = 0; i < Nr; i++) {
            for(int j = 0; j < Nc; j++) {
                data[i+r][j+c] = function(data[i+r][j+c]);
            }
        }
    }
    
    std::string toString() {
        std::string s = std::to_string(Nr)+"x"+std::to_string(Nc)+"\n";
        
        for(int i = 0; i < Nr; i++) {
            for(int j = 0; j < Nc; j++) {
                s += std::to_string(data[i+r][j+c])+" ";
            }
            
            s+="\n";
        }
        
        
        return s;
    }
    
       
};

#endif /* ARR_H */

