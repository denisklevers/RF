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
#include <iomanip>

namespace tools {

double** createDoubleArray2D(int Nr, int Nc);
void     freeDoubleArray2D(double** A, int Nr);

void wait(int ms);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
 
    Custom structures
 
 
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum printOrN{
  quiet= 0,
  loud,
};


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
    
    ~IndexedData() {
        freeDoubleArray2D(data,rows);
    }
    
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
    
    return max(in.data, in.length);
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
    
    return min(in.data, in.length);
}

template<typename T> T sum(arr<T> A) {
    
    T sum = A[1];
    
    for(int i = 1; i < A.length; i++) {
        sum += A[i];
    }
    
    return sum;
}

template<typename T> arr<T> add(arr<T> A1, arr<T> A2) {
   
    arr<T> A;
    arr<T> ret = (A1.length > A2.length) ? (A = A2, copy(A1)) : (A = A1, copy(A2));
    
    for(int i = 0; i < A.length; i++) {
        ret.data[i] += A.data[i];
    }
    
    return ret;
}

template<typename T> arr<T> d(arr<T> A, int lag) {
    T* newA = new T[A.length-lag];
    
    for(int i = lag; i < A.length;i++) {
        newA[i-lag] = A[i] - A[i-lag];
    }
    
    return {newA, A.length-lag};
}



template<typename T> arr<T> d_p(arr<T> A, int lag) {
    T* newA = new T[A.length-lag];
    
    for(int i = lag; i <A.length;i++) {
        if(A[i-lag]!= 0) {
            newA[i-lag] = (A[i] - A[i-lag])/A[i-lag];
        } else {
            throw std::overflow_error("arr::d_p - Divide by zero");
        }
    }
    
    return {newA, A.length-lag};
}


template<typename T> arr<T> copy(arr<T> A) {
    T* newA = new T[A.length]; 
   
    std::copy(A.data, A.data+A.length, newA);
        
    arr<T> RA = {newA, A.length};
    
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
   
    return mean(A, 0, A.length);
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

template<typename T> arr<T> normalize_via_mean(arr<T> in) {
    
    T* ret = new T[in.size];
    
    doubledouble m = mean(in);
    
    for(int i = 0; i < in.size; i++) {
        ret[i] = (in[i] - m.x)/m.y;
    }
    
    return {ret, in.size()};
}

template<typename T> arr<T> normalize_via_minmax(arr<T> in) {
    
    T* ret = new T[in.size];
    
    double min = min(in);
    double max = max(in);
    
    for(int i = 0; i < in.size; i++) {
        ret[i] = in[i]/(max-min);
    }
    
    return {ret, in.size()};
}


template<typename T> double correlation(arr<T> A, arr<T> B, int lag = 0) {
    if(A.length == B.length) {
        doubledouble m_A = mean(A,lag,A.length);
        doubledouble m_B = mean(B,0,B.length-lag);

        // Calc correlation
        double corr = 0;
   
        for(int i = lag; i < A.length; i++) {
            corr += (A[i]-m_A.x)*(B[i-lag]-m_B.x);
        }
        
        corr /= m_A.y*m_B.y*(A.length-lag);
        
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
    doubledouble m_A = mean(A,lag,A.length);
    doubledouble m_B = mean(A,0,A.length-lag, function); // Note: filtered mean
    
    // Calc correlation
    double acorr = 0;
    int c = 0;
    
    for(int i = lag; i < A.length; i++) {
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

IndexedData* loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol);




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
    emp_distribution();
    emp_distribution(arr<T>, double bsize = 0.001);
    emp_distribution(arr<T>, int);
    ~emp_distribution()
    {	
	//std::cout << "An empirical distribution has been destroyed." << std::endl;
    }
    
    void show_data();
    
    doubledouble min_max();
    
    arr<value_freq> get_histogramm();
    
    emp_distribution operator+(emp_distribution&);
    
    void add_values(arr<T>, printOrN state = loud);
    T mean();
    T var();
    T skewness();
    T kurtosis();
    // arr<T> resample(int);
    // kernel for function pointer 
    
private:
    LinkedList<value_freq> * histo;
    T Min;
    T Max;
    double binsize;
    
    int SampleSize;
};

template <class T>
emp_distribution<T>::emp_distribution(){
}

template <class T>
emp_distribution<T>::emp_distribution(arr<T> input, double bsize){
    
    Min = min(input);
    Max = max(input);
    binsize= bsize;
    
    SampleSize = input.size();
    
    std::cout << std::fixed <<  std::setprecision(5) 
              << "Distribution from sample: sample size = " << SampleSize <<  ", (min,max) = ("; 
    std::cout << Min << " , " << Max << ")."<< std::endl;
   
    
    // Create histogram for given binsize
    
    // Finding positions of bin_lefts
    
    int OffsetTo0 = static_cast<int>((Min - binsize/2)/binsize);
    double rmin = binsize/2 + OffsetTo0*binsize;
    int LastBin= static_cast<int>((Max - rmin)/binsize);
    double rmax = rmin + LastBin*binsize;
 
    
    int N = (rmax - rmin)/binsize + 1;
   
    
    std::cout << "First and last bin lefts: ("<< rmin << "," << rmax <<  "), binned by "<< N << " bins, size = " << bsize << "."<< std::endl;
    
    LinkedList<value_freq> * binlist = new LinkedList<value_freq> ();
    
    // Setting bin centers
    for(int i=0; i< N; i++){
        binlist->add({rmin + (i + 0.5)*binsize, 0});
    }
    
    int k = 0;
    for(int i=0; i< input.size(); i++){
        k = static_cast<int>((input[i] - rmin)/binsize);
        binlist->get(k)->frequency ++;
    }
    
    histo = binlist;
    
}

template <class T>
emp_distribution<T>::emp_distribution(arr<T> input, int N){
    
    
    Min = min(input);
    Max = max(input);
    
    SampleSize = input.size();
    
    std::cout << std::fixed <<  std::setprecision(5) 
              << "Distribution from sample: sample size = " << SampleSize <<  ", (min,max) = ("; 
    std::cout << Min << " , " << Max << ")."<< std::endl;
    
    // Create histogram for given number of bins
 
    binsize = (Max - Min)/N;
    
    // Finding bin positions
    
    int OffsetTo0 = static_cast<int>((Min - binsize/2)/binsize);
    double rmin = binsize/2 + OffsetTo0*binsize;
    int LastBin= static_cast<int>((Max - rmin)/binsize);
    double rmax = rmin + LastBin*binsize;
    
    
    std::cout << "First and last bin lefts: ("<< rmin << "," << rmin + N*binsize <<  "), binned by "<< N << " bins, size = " << binsize << "."<< std::endl;
    
    LinkedList<value_freq> * binlist = new LinkedList<value_freq> ();
    
    // Setting bin centers
    for(int i=0; i< N; i++){
        binlist->add({rmin + (i + 0.5)*binsize, 0}) ;
    }
    
    int k = 0;
    for(int i=0; i< input.size(); i++){
        k = static_cast<int>((input[i] - rmin)/binsize);
        binlist->get(k)->frequency ++;
    }
   
    histo = binlist;
}


/* +-operator for two distributions */
template <class T>
emp_distribution<T>  emp_distribution<T>::operator+(emp_distribution& d){
    
    // Copy first distribution to distSum.
    
    // TO DO: Write as copy constructor later.
    
    double binsize1 = this -> binsize;
    double binsize2 = d.binsize;
    
    arr<value_freq> finerHisto;
    
    emp_distribution distSum;
    
    if(binsize1 > binsize2){
        distSum = *this;
        
        finerHisto = d.get_histogramm();
    } else{
        distSum = d;
        
        finerHisto = this->get_histogramm();
    }
    
    int len = finerHisto.size();
    
    for(int i = 0; i < len; i++){
        int binHeight = finerHisto[i].frequency;
        
        for(int j = 0; j <binHeight; j++){
            double temp[1]={finerHisto[i].value};
            distSum.add_values({temp,1}, quiet);
        }
        
    }
    
    return distSum;
}


template <class T>
void emp_distribution<T>::show_data(){
    std::cout << "Distribution of sample size " << SampleSize << " and bin lefts at (Min,Max) = (" << Min;
    std::cout << "," << Max << ")." << std::endl;
    std::cout << "(Mean,var,skewness,kurtosis) = ("<< mean()<< ","<< var() << ","<< skewness() << ","<< kurtosis() << ")." << std::endl;
}

template <class T>
void emp_distribution<T>::add_values(arr<T> added, printOrN state){
  
    
    T nMin = min(added);
    T nMax = max(added);
    
    SampleSize += added.length;
    int N = histo->size();
    
    // Rounding
    double rmin = histo->get(0)->value - 0.5*binsize;
    double rmax = histo->get(N-1)->value - 0.5*binsize;
   
    // Resizing of linked list if min or max exceed old min or max
    
    if(nMin < rmin){
        int k = ceil((rmin - nMin)/binsize);
        
        for(int i=1; i<=k; i++)
            histo->addFirst({rmin - i*binsize + 0.5 * binsize,0});
        
        Min = nMin;
        rmin = histo->get(0)->value - 0.5*binsize;
    }
     
    if(nMax >= rmax + binsize){
        int k = floor((nMax - rmax)/binsize);
        
        for(int i=1; i<=k; i++)
            histo->add({rmax + i*binsize + 0.5 * binsize,0});
        
        Max = nMax;
        rmax = histo->getLast()->value - 0.5*binsize;
    }
 
   
    // Appending the histogram
   
    int k = 0;
    for(int i=0; i< added.length; i++){
        k = static_cast<int>((added[i] - rmin)/binsize);
        histo->get(k)->frequency ++;
    }  
    
    
    N = histo->size();
    
    
    // Print updated distribution information.
    if(state == loud){
        std::cout << std::fixed <<  std::setprecision(5) 
              << "Distribution updated: sample size = " << SampleSize <<  ", (min,max) = ("; 
        std::cout << Min << " , " << Max << ")."<< std::endl;
        std::cout << "Binned ("<< rmin << "," << rmax <<  ") by "<< N << " bins, size = " << binsize << "."<< std::endl;
    }
}

// Convert histogram given as linked list into array of value_freq pairs.

template <class T>
arr<value_freq> emp_distribution<T>::get_histogramm()
{
    int N = histo->size();
    
    value_freq* ret = new value_freq[N];
   
    for(int i=0; i < N; i++){
        ret[i] = *(histo->get(i));
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
    
    int N = histo->size();
    
    for(int i=0; i < N; i++)
	sum += (histo->get(i)->value) * (histo->get(i)->frequency);
	
    return sum/SampleSize ;
}

template <class T>
T emp_distribution<T>::var(){
    double sum=0;
    
    int N = histo->size();
    T m = mean();
    
    for(int i=0; i < N; i++)
	sum += pow(2,histo->get(i)->value - m) * (histo->get(i)->frequency);
	
    return sum/(SampleSize-1) ;
}

template <class T>
T emp_distribution<T>::skewness(){
    double sum=0;
    
    int N = histo->size();
    T m = mean();
    T sig = sqrt(var());
    
    for(int i=0; i < N; i++)
	sum += pow(histo->get(i)->value - m,3)/pow(sig,3) * (histo->get(i)->frequency);
	
    return sum/SampleSize ;
}

template <class T>
T emp_distribution<T>::kurtosis(){
    double sum=0;
    
    int N = histo->size();
    T m = mean();
    T sig = sqrt(var());
    
    for(int i=0; i < N; i++)
	sum += pow(histo->get(i)->value - m,4)/pow(sig,4) * (histo->get(i)->frequency);
	
    return sum/SampleSize ;
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

template <typename T>
void printH(T histo)
{
	for(int i = 0; i< histo.size(); i++)
		std::cout << "Value X = " << histo[i].value <<  " : " << histo[i].frequency << " (Frequency)" << std::endl;
}
}



#endif /* TOOLS_H */

