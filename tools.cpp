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

randUniInt::randUniInt(int l, int h) {
    
    dist = std::uniform_int_distribution<int>(l,h);
    rng = std::mt19937(std::time(0));
}

int randUniInt::next() {
    return dist(rng);
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
}
    
IndexedData loadAndIndexDataFromCSV(const char *filename, int Nr, int Nc, int startPos, int keyCol) {
    double** M = createDoubleArray2D(Nr,Nc);
    
    loadCSV(filename, M, Nr, Nc, startPos);
    
    IndexedData ret = {M, Nr, Nc, keyCol, hashmap<intint>()};
    
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
           
            ret.index.add(lastKey, len);
            
            lastKey = M[i][keyCol];
            c = 0;
        }
        
        c++;
    }
    
    return ret;
}

// Random variable


RandomVariable::RandomVariable(std::vector<int> Xs, std::vector<double> ps)
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


double RandomVariable::inverseCDF(double p)
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


int RandomVariable::OneDraw()
{
	std::uniform_real_distribution<double> distr(0.0, 1.0);
	
	return inverseCDF(distr(rng));
}


std::vector<int> RandomVariable::Sample(int SampleSize)
{
	std::uniform_real_distribution<double> distr(0.0, 1.0);
	
	std::vector<int> *ret =  new std::vector<int>(SampleSize);       // Put entire vector on heap
	
	for(int i=0; i<SampleSize; i++)
	{
		ret->at(i) = inverseCDF(distr(rng));
	}
	
	return *ret;
	
}

void RandomVariable::showData()
{
	std::cout<< "The random variable X is defined by the sample space and probabilities \n" ;
	for(int i=0; i<samplespace.size(); i++)
	{
		std::cout<< "X:" << samplespace.at(i) << ", p(X=" << samplespace.at(i) << ")=" ;
		std::cout<<  probs.at(i) << std::endl; 
	}
}

double RandomVariable::mean()
{
	double sum=0;
	
	for(int i=0; i < samplespace.size(); i++)
		sum += samplespace.at(i)*probs.at(i);
	
	return sum;
	
}; 												

double RandomVariable::median()
{
	return samplespace.at(static_cast<int>(samplespace.size()/2)-1);
}; 											


double RandomVariable::var()
{
	double sum=0;
	
	for(int i=0; i < samplespace.size(); i++)
		sum += (samplespace.at(i)-mean())*(samplespace.at(i)-mean())*probs.at(i);
		
	return sum;
}; 

// Printing Histogramm:

void printH(std::vector<value_freq> histo)
{
	for(int i = 0; i< histo.size(); i++)
		std::cout << "Value X = " << histo.at(i).value <<  " : " << histo.at(i).frequency << " (Frequency)" << std::endl;
}
