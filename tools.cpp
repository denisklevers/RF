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


coinFlipper::coinFlipper() {
    coinFlipper(0.5);
}

coinFlipper::coinFlipper(double bias) {
    p = bias;
    
    rng = std::mt19937(std::time(0));
}

bool coinFlipper::coinFlip() {
    std::uniform_real_distribution<double> unif_dist(0, 1);
        
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
    
    IndexedData ret;
    ret.data   = M;
    ret.keyCol = keyCol;
    ret.index  = hashmap<intint>();
    
    // Index data
    int c = 0;
    int lastKey = M[0][keyCol];
    
    for(int i=1; i < Nr; i++) 
    {
        if((M[i][keyCol]!=lastKey)||(i == Nr-1)) 
        {
            intint len;
            len.A = i;
            len.B = c;
           
            ret.index.add(lastKey, len);
            
            lastKey = M[i][keyCol];
            c = 0;
        }
        
        c++;
    }
    
    return ret;
}