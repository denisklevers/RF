/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <cstdlib>
#include <stdio.h>
#include <iostream>

#include "simu.h"
#include "tools.h"
#include "uthash.h"
#include "hashmap.h"

using namespace std;

/*
 * 
 */
int main() {
    cout << "Loading data...\n";
    
    // Init data
    int Nc = 9;
    int Nr = 100000;
    
    IndexedData data = loadAndIndexDataFromCSV("/home/krefl/storage/data/NY_M_MRK_USD.csv", Nr, Nc, 1, 1);
    
    simu Sim = simu(&data, 0, 100);
   
    state S = Sim.next(1);
   
    /*
    cout << S.toString() << endl;
    
    S.r = 1000;
    S = Sim.next(S, 0);
    
    cout << S.toString() << endl;
    
    S = Sim.next(0);
    S = Sim.next(0);
   
    cout << S.toString() << endl;
    
    */
    
    int c = 0;
    while(!(Sim.EoD())) {
        S = Sim.next(0);
        cout << S.toString() << endl;
        c++;
    } 
    
    cout << "Done!";
    
    return 0;
}

