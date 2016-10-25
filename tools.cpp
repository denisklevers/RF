/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <random>
#include "hashmap.h"
#include "tools.h"
#include <typeinfo>
 #include <time.h>

namespace tools {

   
void wait(int ms) {
    struct timespec time;
    time.tv_sec = ms / 1000;
    time.tv_nsec = (ms % 1000) * (1000 * 1000);
    nanosleep(&time,NULL);
}
   
randUniInt::randUniInt(int l, int h) {
    
    dist = std::uniform_int_distribution<int>(l,h);
    rng = std::mt19937(std::time(0));
}

int randUniInt::next() {
    return dist(rng);
}

int randUniInt::nextSkip(int skip) {
    
    int r;
    
    do 
    {
        r = dist(rng); 
    } while(r==skip);
    
    return r;    
        
}

int randUniInt::nextSkip(int skip[], int size) {
    int r;
    
    do 
    {
        r = dist(rng); 
    } while(inQ(r, skip, size));
    
    return r;    
        
}

coinFlipper::coinFlipper(double bias) {
    p = bias;
    
    rng = std::mt19937(std::time(0));
}

bool coinFlipper::coinFlip() {
     
    return (unif_dist(rng) < p) ? 1 : 0 ;
}
    


double** createDoubleArray2D(int Nr, int Nc) {
    int i;
    
    double **A = (double**) malloc(Nr * sizeof(double *));
    
    
    for (i=0; i<Nr; i++)
    {
        A[i] = (double*) malloc(Nc * sizeof(double));
    }

    return A;
}

void freeDoubleArray2D(double** A, int Nr) {
    int i;
    
    for(i=0; i < Nr; i++) {
        free(A[i]);
    }
    
}


void loadCSV(const char *filename, double** M, int Nr, int Nc, int startPos) {
    char buffer[1024*8];
    char *line,*record;
    int i,j;
    
    FILE *fstream = fopen(filename, "r");

    // Ignore rows < startPos
    for(i = 0; i < startPos; i++) 
    {
        fgets(buffer,sizeof(buffer),fstream);
    }
    
    // Read rows
    for(i = 0; i < Nr; i++) 
    {
        line = fgets(buffer,sizeof(buffer),fstream);
        
        record = strtok(line,",");
        
        // Read cols
        for(j=0; j < Nc; j++) {
          
            M[i][j] = atof(record);
           
            record = strtok(NULL,",");
        }
    }
    
    fclose(fstream);
}
    
void saveCSV(const char *filename, double** M, int Nr, int Nc) {
    
    FILE *fstream = fopen(filename, "w");
  
    for(int r = 0; r < Nr; r++) {
        std::string s; 
       
        for(int c = 0; c < Nc; c++) {
            
           s += std::to_string(M[r][c]);
           
           if(c < Nc-1) s+= ",";
        }
       
        s += "\n";
         
        fputs(s.data(), fstream);
    }
   
    fclose(fstream);
}


IndexedData* loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol) {
    double** M = createDoubleArray2D(Nr,Nc);
    
    loadCSV(filename, M, Nr, Nc, startPos);
    
    IndexedData* ret = new IndexedData{M, Nr, Nc, keyCol, hashmap<intint>()};
    
    // Index data
    int c = 1;
    int lastKey = M[0][keyCol];
    
    for(int i=1; i < Nr; i++) 
    {
        if((M[i][keyCol]!=lastKey)||(i == Nr-1)) 
        {
            intint len;
            len.A = i-c;
            len.B = c;
           
            ret->index.add(lastKey, len);
            
            lastKey = M[i][keyCol];
            c = 0;
        }
        
        c++;
    }
    
    return ret;
}

// Random variable

template <class T>
RandomVariable<T>::RandomVariable(std::vector<T> Xs, std::vector<double> ps)
{
	samplespace =  Xs;
	probs = ps;
	
	double sum;
	for(int i=0; i< Xs.size(); i++)
		sum+=ps[i];
		
	if(sum != 1)
		std::cout << "Ill-defined probabilities: Sum is " << sum << "."<< std::endl;
	
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        rng = std::mt19937(seed);
}

template <class T>
T RandomVariable<T>::inverseCDF(double p)
{
	int k = 0;
	double test = 0;
	while(test < p)
	{
		test+= probs[k];
		k++;
	}
	
	return samplespace.at(k-1);
}

template <class T>
T RandomVariable<T>::OneDraw()
{
	std::uniform_real_distribution<double> distr(0.0, 1.0);
	
	return inverseCDF(distr(rng));
}

template <class T>
std::vector<T> RandomVariable<T>::Sample(int SampleSize)
{
	std::uniform_real_distribution<double> distr(0.0, 1.0);
	
	std::vector<T> *ret =  new std::vector<T>(SampleSize);       // Put entire vector on heap
	
	for(int i=0; i<SampleSize; i++)
	{
		ret->at(i) = inverseCDF(distr(rng));
	}
	
	return *ret;
	
}

template <class T>
void RandomVariable<T>::showData()
{
	std::cout<< "The random variable X is defined by the sample space and probabilities \n" ;
	for(int i=0; i<samplespace.size(); i++)
	{
		std::cout<< "X:" << samplespace.at(i) << ", p(X=" << samplespace.at(i) << ")=" ;
		std::cout<<  probs.at(i) << std::endl; 
	}
}

template <class T>
T RandomVariable<T>::mean()
{
	double sum=0;
	
	for(int i=0; i < samplespace.size(); i++)
		sum += samplespace.at(i)*probs.at(i);
	
	return sum;
	
}; 												

template <class T>
T RandomVariable<T>::median()
{
	return samplespace.at(static_cast<int>(samplespace.size()/2)-1);
}; 											

template <class T>
T RandomVariable<T>::var()
{
	double sum=0;
	
	for(int i=0; i < samplespace.size(); i++)
		sum += (samplespace.at(i)-mean())*(samplespace.at(i)-mean())*probs.at(i);
		
	return sum;
}; 

// No need to call this TemporaryFunction() function,
// it's just to avoid link error.
void TemporaryFunction ()
{
    std::vector<int> a (1);
    std::vector<double> b (1);
    RandomVariable<int> TempObj(a,b);
}

// Printing Histogramm:

void printH(std::vector<value_freq> histo)
{
	for(int i = 0; i< histo.size(); i++)
		std::cout << "Value X = " << histo.at(i).value <<  " : " << histo.at(i).frequency << " (Frequency)" << std::endl;
}

}