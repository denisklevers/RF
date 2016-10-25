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

#include "operators.h"
/*
#include "Visu.h"
*/

using namespace std;
using namespace ops;

int main(int argc, char *argv[]) {
    cout << "Loading data...\n";
    
    // Init data
    int Nc = 10;
    int Nr = 152100;
  
    
    IndexedData data = loadAndIndexDataFromCSV("/Users/denis/Documents/University/Dropbox/Work/NY_M_AMZN_USD.csv", Nr, Nc, 1, 1);
   
    /*
    
    LinkedList<sca_op*> O;
    O.add(new ops::mean);
    
    sca_op *X = *O.get(0);
    
    double test[3] = {1,2,3};
    arr<double> A = {test,3};
    
    double Y = X->apply(A);
    
    cout << to_string(Y) << endl;
    */
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
    int depth = 10;
    randUniInt randInt(0,4);
    
    simu Sim = simu(&data, 0, 5000, 0.85,1);
    /*
    LinkedList<int> Alist; 
    double P[] = {0,20,20,10};
    
    state S = Sim.getState();
    
    cout << S.toString() << endl;
    
    while(!(Sim.EoD())) {
    
        int a = Sim.searchBestAction_MKT_naiveMC(P,10000,30);
        
        Alist.add(a);
        
        order O = {a,1,0};
        
        if(a!=0) {
            S = Sim.next(&O);
        } 
        else {
            S = Sim.next(NULL);
        } 
           
        cout << S.toString() << endl;
    }   
    
    cout << Alist.toString() << endl;
   
   
    */
    cout << "Done!";
    
    return 0;
}

