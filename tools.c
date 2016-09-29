/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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