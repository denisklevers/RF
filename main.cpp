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
    
    double values[4] = {121.1111,121.2,121.4,125.1343};
    arr<double> sample = {values,4};
    emp_distribution<double> h(sample, 0.4);
    
    arr<value_freq> his= h.get_histogramm();
    printH(his);
    
    double values1[3] = {118.485043,119.1111,127.130};
    arr<double> sample1 = {values1,3};
    emp_distribution<double> h1(sample1, 0.8);
    
  
    arr<value_freq> his1= h1.get_histogramm();
    printH(his1);
    
    emp_distribution<double> sum = h + h1;
    
    arr<value_freq> hisSum= sum.get_histogramm();
    
    cout << "Sum histogram" << endl;
    printH(hisSum);
    
    sum.show_data();
  
  /*
    IndexedData data = loadAndIndexDataFromCSV("/Users/denis/Documents/University/Dropbox/Work/NY_M_AMZN_USD.csv", Nr, Nc, 1, 1);
   
    
    
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
    /*
    simu Sim = simu(&data, 0, 5000, 0.85,1);
    
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

