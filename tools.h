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
#include <iostream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Custom structures
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


struct intint 
{
    int A;
    int B;
};

struct doubledouble
{
    double x;
    double y;
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
    
    
    void multiply(double C) {
        for(int i = 0; i < size; i++) {
            data[i] *= C;
        }
    }
    
    void divide(double C) {
        if(C!=0) {
            multiply(1/C);
        }
        
        throw std::overflow_error("arr::divide - Divide by zero");
    }
    
    void add(double C) {
        for(int i = 0; i < size; i++) {
            data[i] += C;
        }
    }
    
    void sub(double C) {
        for(int i = 0; i < size; i++) {
            data[i] -= C;
        }
    }
    
    void set(double C) {
        for(int i = 0; i < size; i++) {
            data[i] = C;
        }
    }
    
    /*
        Applies the supplied function  element-wise 
     *  f: <T> -> <T>
     */
    void apply(T (*function)(T)) {
        for(int i = 0; i < size; i++) {
            data[i] = function(data[i]);
        }
    }
    
    std::string toString() {
        std::string s = "L: "+std::to_string(size)+"\n[ ";
        
        for(int i = 0; i < size; i++) {
            s += std::to_string(data[i])+" ";
        }
        
        return s+"]";
    }
    
};

struct IndexedData
{
    double** data;
    int rows;
    int cols;

    int keyCol;
    hashmap<intint> index;
    
    arr<double> getCol(int col) 
    {
        return getCol(col, 0, rows);
    }
    
    /*
        Get column col
        [r1,r2)
     
     */
    arr<double> getCol(int col, int r1, int r2) 
    {
        
        if(col < cols && r1 >= 0 && r2 <= rows && r1 <= r2) 
        {
          
            // Prepare data
            double* A = new double[r2-r1];
            
            for(int i = r1; i < r2; i++) {
                A[i-r1] = data[i][col];
            }
       
            return {A, r2-r1};
        }
        
        throw std::out_of_range("IndexedData::getCol - Invalid indices");
    }
    
    arr<double> getColOfDay(int col, int day) {
        if(index.exist(day)) {
            intint* pos = index.get(day);
            
            return getCol(col, pos->A, pos->A + pos->B);
        }
        
        throw std::out_of_range("IndexedData::getDayCol - Invalid day");
    }
    
    arr<double> getColOfRandomDay(int col) {
        intint* pos = index.random();
        
        return getCol(col, pos->A, pos->A + pos->B);
    }
    
};




// Struct for Binner

struct value_freq
{
	double value;
	int frequency;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Array tools
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

template<typename T> arr<T> d(arr<T> A, int lag) {
    T* newA = new T[A.size-lag];
    
    for(int i = lag; i < A.size;i++) {
        newA[i-lag] = A[i] - A[i-lag];
    }
    
    return {newA, A.size-lag};
}

template<typename T> arr<T> d_p(arr<T> A, int lag) {
    T* newA = new T[A.size-lag];
    
    for(int i = lag; i <A.size;i++) {
        if(A[i-lag]!= 0) {
            newA[i-lag] = (A[i] - A[i-lag])/A[i-lag];
        } else {
            throw std::overflow_error("arr::d_p - Divide by zero");
        }
    }
    
    return {newA, A.size-lag};
}


template<typename T> arr<T> copy(arr<T> A) {
    T* newA = new T[A.size]; 
   
    std::copy(A.data, A.data+A.size, newA);
        
    arr<T> RA = {newA, A.size};
    
    return RA;
}

/**
 *  Calculates mean and sdev of array elements
 * 
 *  Return
 *  x: mean
 *  y: sample sdev
 */
template<typename T> doubledouble mean(arr<T> A) {
   
    return mean(A, 0, A.size);
}

/**
 *  Calculates mean and sdev of sub-array elements
 *  Sub-array [s,e)
 * 
 *  Return
 *  x: mean
 *  y: sample sdev
 */
template<typename T> doubledouble mean(arr<T> A, int s, int e) {
   
    // Calc mean
    double m = 0;
    
    for(int i = s; i < e; i++) {
        m += A[i];
    }
    
    m /= e-s;
    
    // Calc var
    double var = 0;
    
    for(int i = s; i < e; i++) {
        var += std::pow(A[i]-m,2);
    }
    
    return {m, std::sqrt(var/(e-s))}; // StDev or sample StDev ?
}

/**
 *  Calculates (lagged) autocorrelation of array elements
 *  (for stationary process)
 *  
 */
template<typename T> double autoCorellation(arr<T> A, int lag = 0) {
   
    return corellation(A,A,lag);
}

template<typename T> double corellation(arr<T> A, arr<T> B, int lag = 0) {
    if(A.size == B.size) {
        doubledouble m_A = mean(A,lag,A.size);
        doubledouble m_B = mean(B,0,B.size-lag);

        // Calc correlation
        double acorr = 0;
   
        for(int i = lag; i < A.size; i++) {
            acorr += (A[i]-m_A.x)*(B[i-lag]-m_B.x);
        }
        
        acorr /= m_A.y*m_B.y*(A.size-lag);
        
        return acorr;
    }
    
    throw std::out_of_range("correlation - Need equal size arrays");
    
}

// ToDo: Correlation with filter !


// Print vector

template <typename T>
void printV(std::vector<T> vec)
{
	for(int i=0; i < vec.size() ; ++i)
		std::cout << vec[i] << std::endl;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    .CSV tools
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
 
void        loadCSV(const char *filename, double** M, int Nr, int Nc, int startPos);
IndexedData loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol);




/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Probability tools 
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


class coinFlipper {
public:
    coinFlipper(double bias = 0.5);
    bool coinFlip();
    
private:
    
    std::mt19937 rng;
    
    double p;
};


class RandomVariable{
public:
	// RandomVariable();
	// double DrawURN(double a, double b);
	
	RandomVariable(std::vector<int>, std::vector<double> );
	~RandomVariable()
	{	
	std::cout << "A random discrete variable has been destroyed." << std::endl;
	}
	
	double inverseCDF(double p);
	
	double mean(); 												//Only valid for numbers
	double var(); 												//Only valid for numbers
	double median(); 											
	
	int OneDraw();
	std::vector<int> Sample(int SampleSize);
	void showData();
	
private:
	std::mt19937 rng;
	
	std::vector<int> samplespace;
	std::vector<double> probs;
	
	// double a, b;
};





// Binning into Histogramm

template <typename T>
std::vector<value_freq> HistogramMaker(std::vector<T> &sample, std::vector<T> samplespace)
{
	int N = sample.size();
	int k = samplespace.size();
	
	std::vector<value_freq> *ret= new std::vector<value_freq>(k);
	
	for(int i=0; i<k; i++)
		ret->at(i).value = samplespace[i];
	
	for(int i=0; i<N; i++)
	{
		int pos = find(samplespace.begin(), samplespace.end(),sample[i]) - samplespace.begin();
		std:: cout << pos << std::endl;
		
		ret->at(pos).frequency++;
	}
	
	return *ret;
}

// Printing Histogramm:

void printH(std::vector<value_freq> histo);


#endif /* TOOLS_H */

