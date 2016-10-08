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
    
    IndexedData data = loadAndIndexDataFromCSV("/Users/krefl/data/NY_M_AMZN_USD.csv", Nr, Nc, 1, 1);
    
    simu Sim = simu(&data, 0, 50, 0.85);
    order O = {1, 50, 0};
    
    state S = Sim.next(&O);
    cout << S.toString() << endl;
   
    S = Sim.next(NULL);
    cout << S.toString() << endl;
 
    S = Sim.next(NULL);
    cout << S.toString() << endl;
    
    O = {1,50,data.data[S.r][4]+5};
    S = Sim.next(&O);
    cout << S.toString() << endl;
   
    
    while(!(Sim.EoD())) {
        S = Sim.next(NULL);
        cout << S.toString() << endl;
    } 
  
    cout << "Done!";
    
    return 0;
}

