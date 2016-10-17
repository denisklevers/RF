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
#include "LinkedList.h"
#include "analyzer.h"
/*
#include "Visu.h"
*/

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Loading data...\n";
    
    // Init data
    int Nc = 10;
    int Nr = 152100;
  
    IndexedData data = loadAndIndexDataFromCSV("/Users/krefl/data/NY_M_AMZN_USD.csv", Nr, Nc, 1, 1);
    
    /*
    
    analyzer Analy = analyzer(&data);
    
    auto T = [](arr2D<double> M) 
    {
        auto C = [](double d) {return d > 0.0005;};
   
        double A = autoCorrelation_filtered<double>(d_p(M.getCol(5),1),1,C);
        cout << to_string(A)<< endl;
        return A;
    
    };
  
    */
  
    int Nmc   = 1000;
    int depth = 5;
    randUniInt randInt(0,4);
    simu Sim = simu(&data, 0, 10, 0.85);
    LinkedList<int> Alist; 
    
    state S = Sim.getState();
        
   
    while(!(Sim.EoD())) {
        
        double R[4] = {0,0,0,0};
        
        // MC runs
        for(int m = 0; m < Nmc; m++) {
            
            Sim.setState(S);
        
            int r = randInt.next();
        
            if(S.PF.pos!=0) {
                while(r==1 || r==2) {
                    r = randInt.next();
                }
            }
            
            if(S.PF.pos==0) {
                while(r==3) {
                    r = randInt.next();
                }
            }
            
            order O = {r,1,0};
            
            // MC depth run
            for(int i = 0; i < depth; i++) {
                // Generate random order
                Sim.next(&O);
            
                O.action = randInt.next();
            }
            
            state T = Sim.getState();
        
            R[r] += T.upnl+T.rpnl;
        }
       
        int a = posOfFirstMax<double>(R, 4);
        Alist.add(a);
        order O = {a,1,0};
        
        S = Sim.next(S, &O);
        
        cout << S.toString() << endl;
    } 
 
    cout << Alist.toString() << endl;
    
    cout << "Done!";
    
    return 0;
}

