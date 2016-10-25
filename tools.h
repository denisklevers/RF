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
#include "arr.h"
#include <math.h>    
#include "LinkedList.h"

namespace tools {

double** createDoubleArray2D(int Nr, int Nc);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Custom structures
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum relOp 
{
    l,
    s,
    e,
    le,
    se,
};

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






struct IndexedData
{
    double** data;
    int rows;
    int cols;

    int keyCol;
    hashmap<intint> index;
    
    arr2D<double> getSubMatrix(int r0, int c0, int Nr, int Nc) {
        double** A = createDoubleArray2D(Nr,Nc);
        
        for(int i = 0; i < Nr; i++) {
            memcpy(A[i], data[r0+i]+c0, Nc);
        }
        
        arr2D<double> R;
        R.Nr = Nr;
        R.Nc = Nc;
        R.data = A;
        
        return R;
    }
    
    arr2D<double> getSubMatrixAsView(int r0, int c0, int Nr, int Nc) {
        
        arr2D<double> R = arr2D<double>(r0, c0);
        R.Nr = Nr;
        R.Nc = Nc;
        R.data = data;
        
        return R;
    }
    
    /*
     *   Get row
     *   [c1,c2)
     *
     */
   
    arr<double> getRow(int row, int c1, int c2) {
        
        if(row < rows && c1 >= 0 && c2 <= cols && c1 <= c2) 
        {
            // Prepare data
            double* A = new double[c2-c1];
            
            for(int i = c1; i < c2; i++) {
                A[i-c1] = data[row][i];
            }
       
            return {A, c2-c1}; 
        }
        
        throw std::out_of_range("IndexedData::getRow - Invalid indices");
  
    }
    
    arr<double> getRow(int row) 
    {
        return getRow(row, 0, cols);
    }
    
    
    arr<double> getCol(int col) 
    {
        return getCol(col, 0, rows);
    }
    
    /*
     *   Get column col
     *   [r1,r2)
     *
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
    
    
    std::string toString() {
        std::string s;
        
        s += std::to_string(rows)+"x"+std::to_string(cols)+" | keys: "+std::to_string(index.size());
       
        return s;
    }
    
};




// Struct for Binner

struct value_freq
{
	double value;
	int frequency;
        
        value_freq(){
        }
        
        value_freq(double x, int n)
        {
            value = x;
            frequency = n;
        }
        
        void printDate()
        {
            std::cout << "(" << value << "," << frequency << ")"<< std::endl;
        }
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Array tools
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<typename T> std::string toString(T in[], int size) {
    std::string s = "[ ";
    
    for(int i = 0; i < size; i++) {
        s += std::to_string(in[i])+" ";
    }
    
    return s += "]"; 
    
}

template<typename T> bool inQ(T E, T in[], int size) {
    for(int i = 0; i < size; i++) {
        if(in[i]==E) { return true; }
    }
    
    return false;
}


void     freeDoubleArray2D(double** A, int Nr);

template<typename T> int posOfFirstMax(T* in, int length) {
    
    T max = in[0];
    int pos = 0;
    
    for(int i = 0; i < length; i++) {
        if(in[i]>max) {
            max = in[i];
            pos = i;
        }
    }
    
    return pos;
}

template<typename T> int posOfFirstMax(T in[], int length, int skip) {
    
    int s = -1;
    do {
        s++;
    } while(s==skip);
    
    T max = in[s];
    int pos = s;
    
    for(int i = s+1; i < length; i++) {
        if(in[i] > max && i!=skip ) {
            max = in[i];
            pos = i;
        }
    }
    
    return pos;
}


template<typename T> int posOfFirstMax(T in[], int length, int skip[], int skipLength) {
    
    int s = -1;
    do {
        s++;
    } while(inQ(s, skip, skipLength));
    
    T max = in[s];
    int pos = s;
    
    for(int i = s+1; i < length; i++) {
        if(in[i] > max && !inQ(i, skip, skipLength) ) {
            max = in[i];
            pos = i;
        }
    }
    
    return pos;
}


template<typename T> int count(T* in, T E, int length) {
    int c = 0;
    
    for(int i = 0; i < length; i++) {
        if(in[i]==E) c++;
    }
    
    return c;
}

template<typename T> int countNotIn(T in[], T E, int length) {
    int c = 0;
    
    for(int i = 0; i < length; i++) {
        if(in[i]!=E) c++;
    }
    
    return c;
}

template<typename T> int posOfLastMax(T* in, int length) {
    
    T max = in[0];
    int pos = 0;
    
    for(int i = 0; i < length; i++) {
        if(in[i]>=max) {
            max = in[i];
            pos = i;
        }
    }
    
    return pos;
}

template<typename T> double max(T* in, int length) {
    
    T max = in[0];
    
    for(int i = 0; i < length; i++) {
        if(in[i] > max) {
            max = in[i];
        }
    }
    
    return max;
}

template<typename T> double max(arr<T> in) {
    
    return max(in.data, in.size);
}

template<typename T> double min(T* in, int length) {
    
    T min = in[0];
    
    for(int i = 0; i < length; i++) {
        if(in[i] < min) {
            min = in[i];
        }
    }
    
    return min;
}

template<typename T> double min(arr<T> in) {
    
    return min(in.data, in.size);
}

template<typename T> T sum(arr<T> A) {
    
    T sum = A[1];
    
    for(int i = 1; i < A.size; i++) {
        sum += A[i];
    }
    
    return sum;
}

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
 *  Only elements mapping under function T -> bool = true are taken into account
 * 
 *  Return
 *  x: mean
 *  y: sample sdev
 */
template<typename T> doubledouble mean(arr<T> A, int s, int e, std::function<bool(T)> function ) {
   
    // Calc mean
    double m = 0;
    int    c = 0;
    for(int i = s; i < e; i++) {
        if(function(A[i])) {
            m += A[i];
            c++;
        }
    }
    
    m /= c;
    
    // Calc var
    double var = 0;
    
    for(int i = s; i < e; i++) {
        if(function(A[i])) {
            var += std::pow(A[i]-m,2);
        }
    }
    
    return {m, std::sqrt(var/(c))}; // StDev or sample StDev ?
}



template<typename T> double correlation(arr<T> A, arr<T> B, int lag = 0) {
    if(A.size == B.size) {
        doubledouble m_A = mean(A,lag,A.size);
        doubledouble m_B = mean(B,0,B.size-lag);

        // Calc correlation
        double corr = 0;
   
        for(int i = lag; i < A.size; i++) {
            corr += (A[i]-m_A.x)*(B[i-lag]-m_B.x);
        }
        
        corr /= m_A.y*m_B.y*(A.size-lag);
        
        return corr;
    }
    
    throw std::out_of_range("correlation - Need equal size arrays");
    
}

/**
 *  Calculates (lagged) autocorrelation of array elements
 *  (for stationary process)
 *  
 */
template<typename T> double autoCorrelation(arr<T> A, int lag) {
   
    return correlation(A,A,lag);
}
/**
 *  Calculates (lagged) autocorrelation of array elements
 *  (for stationary process)
 * 
 *  Filtered by function
 * 
 *  Note: Not normalized to \pm 1 anymore
 *  
 */
template<typename T> double autoCorrelation_filtered(arr<T> A, int lag, std::function<bool(T)> function) {
    doubledouble m_A = mean(A,lag,A.size);
    doubledouble m_B = mean(A,0,A.size-lag, function); // Note: filtered mean
    
    // Calc correlation
    double acorr = 0;
    int c = 0;
    
    for(int i = lag; i < A.size; i++) {
        if(function(A[i-lag])) {
            acorr += (A[i]-m_A.x)*(A[i-lag]-m_B.x);
            c++;
        }
    }
        
    acorr /= m_A.y*m_B.y*c;
    
    return acorr;
}


    

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
void        saveCSV(const char *filename, double** M, int Nr, int Nc);

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
    std::uniform_real_distribution<double> unif_dist = std::uniform_real_distribution<double>(0, 1);

    double p;
};

class randUniInt {
public:
    randUniInt(int l, int h);
   
    int next();
    int nextSkip(int skip);
    int nextSkip(int skip[], int size);
    
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
};

template <class T>
class RandomVariable{
public:
	// RandomVariable();
	// double DrawURN(double a, double b);
	
	RandomVariable(std::vector<T>, std::vector<double> );
	~RandomVariable()
	{	
	std::cout << "A random discrete variable has been destroyed." << std::endl;
	}
	
	T inverseCDF(double p);
	
	T mean(); 												
	T var(); 											
	T median(); 											
	
	T OneDraw();
	std::vector<T> Sample(int SampleSize);
	void showData();
	
private:
	std::mt19937 rng;
	
	std::vector<int> samplespace;
	std::vector<double> probs;
	
	// double a, b;
};

template <class T>
class emp_distribution{
    
public:
    emp_distribution(arr<T>, double binsize = 0.01);
    emp_distribution(arr<T>, int);
    ~emp_distribution()
    {	
	std::cout << "An empirical distribution has been destroyed." << std::endl;
    }
    
    void show_data(){
        std::cout << "The minimum and maximum of the " << sample.size() << " values are " << Min;
        std::cout << "," << Max << "." << std::endl;
    };
    
    doubledouble min_max();
    
    arr<value_freq> get_histogramm();
    
    void add_values(arr<T>);
    T mean();
    T var();
    T skewness();
    T kurtosis();
    // arr<T> resample(int);
    // kernel for function pointer 
    
    
private:
    std::vector<T> sample;
    LinkedList<value_freq> histo;
    T Min;
    T Max;
    double binsize;
};

template <class T>
emp_distribution<T>::emp_distribution(arr<T> input, double bsize){
    
    sample = std::vector<T>(begin(input), end(input));
    
    Min = *std::min_element(sample.begin(), sample.end());
    Max = *std::max_element(sample.begin(), sample.end());
    binsize= bsize;
    
    // Create histogram for given binsize
    
    int N = ceil((Max - Min)/binsize);
    
    LinkedList<value_freq> * binlist = new LinkedList<value_freq> ();
    
    for(int i=0; i< N; i++){
        binlist->get(i)->value = Min + i*binsize;
        binlist->get(i)->frequency = 0;
    }
    
    int k = 0;
    for(int i=0; i< sample.size; i++){
        k = static_cast<int>((sample[i] - Min)/binsize);
        binlist->get(k)->frequency ++;
    }
    
    
}

template <class T>
emp_distribution<T>::emp_distribution(arr<T> input, int N){
    
    sample = std::vector<T>(begin(input), end(input));
    
    Min = *std::min_element(sample.begin(), sample.end());
    Max = *std::max_element(sample.begin(), sample.end());
    
    // Create histogram for given number of bins
    
    binsize = static_cast<int>((Max - Min)/N);
    
    LinkedList<value_freq> * binlist = new LinkedList<value_freq> ();
    
    for(int i=0; i< N; i++){
        binlist->get(i)->value = Min + i*binsize;
        binlist->get(i)->frequency = 0;
    }
    
    int k = 0;
    for(int i=0; i< sample.size; i++){
        k = static_cast<int>((sample[i] - Min)/binsize);
        binlist->get(k)->frequency ++;
    }
    
    
}


template <class T>
void emp_distribution<T>::add_values(arr<T> added){
    
    sample = sample.insert(sample.end(),added.begin(), added.end());
    
    T nMin = min(added);
    T nMax = max(added);
    
    // Resizing of linked list if min or max exceed old min or max
    
    if(nMin < Min){
        int k = ceil((Min - nMin)/binsize);
        
        for(int i=1; i<k; i++)
            histo.add_front({Min - i*binsize,0});
        Min = nMin;
    }
    
    if(nMax > Max){
        int k = ceil((nMax - Max)/binsize);
        
        for(int i=1; i<k; i++)
            histo.add({Max + i*binsize,0});
        Max = nMax;
    }
    
    // Appending the histogram
    
    int k = 0;
    for(int i=0; i< sample.size; i++){
        k = static_cast<int>((sample[i] - Min)/binsize);
        histo.get(k)->frequency ++;
    }  
    
}

// Convert histogram given as linked list into array of value_freq pairs.

template <class T>
arr<value_freq> emp_distribution<T>::get_histogramm()
{
    int N = histo.size();
    value_freq* ret = new value_freq[N];
   
    for(int i=0; i<histo.size(); i++){
        ret->value = histo.get(i)->value;
        ret->frequency = histo.get(i)->frequency;
    }
    
    return {ret,N};
}

// return min and max of current distribution

template <class T>
doubledouble emp_distribution<T>::min_max(){
    return {Min,Max};
}

template <class T>
T emp_distribution<T>::mean(){
    double sum=0;
    
    for(int i=0; i < sample.size; i++)
	sum += sample[i];
	
	return sum;
}

template <class T>
T emp_distribution<T>::var(){
    double sum=0;
    
    T m = mean();
    
    for(int i=0; i < sample.size; i++)
	sum += (sample[i]-m)^2;
	
    return sum;
}

template <class T>
T emp_distribution<T>::skewness(){
    double sum=0;
    
    T m = mean();
    T sig = sqrt(var());
    
    for(int i=0; i < sample.size; i++)
	sum += (sample[i]-m)^3/sig^3;
	
    return sum;
}

template <class T>
T emp_distribution<T>::kurtosis(){
    double sum=0;
    
    T m = mean();
    T sig = sqrt(var());
    
    for(int i=0; i < sample.size; i++)
	sum += (sample[i]-m)^4/sig^4;
	
    return sum;
}



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

}

#endif /* TOOLS_H */

