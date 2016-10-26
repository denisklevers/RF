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
#include "arr.h"

#include "operators.h"
#include "Runner.h"
/*
#include "Visu.h"
*/

using namespace std;
using namespace ops;

int main(int argc, char *argv[]) {
    
    // Init data
    int Nc = 10;
    int Nr = 152100;
  
    
 
    //IndexedData data = loadAndIndexDataFromCSV("/Users/krefl/data/NY_M_AMZN_USD.csv", Nr, Nc, 1, 1);
    
    //cout << data.index.getKeySet().toString();
     
    double data[3]={12.14,14.2,15.1445};
    double data1[4]={12.2,14.4,15.3245,16.1};
    
    emp_distribution<double> h({data,3},0.2);
    emp_distribution<double> h1({data1,4},0.2);
    
    emp_distribution<double> sum = h+h1;
    
    arr<value_freq> hist=h.get_histogramm();
    printH(hist);
    cout << "new"<< endl;
    arr<value_freq> hist1=h1.get_histogramm();
    printH(hist1);
    cout << "new"<< endl;
    arr<value_freq> hist2=sum.get_histogramm();
    printH(hist2);
    
    /*
    Runner R(8, "/Users/krefl/data");
    
    auto C = [](simu* Sim) 
    {
        
        double P[] = {0,20,20,10};
   
        int a = Sim->searchBestAction_MKT_naiveMC(P,1000,30);
        
        order O = {a,1,0};
        
        if(a!=0) {
            Sim->next(&O);
        } 
        else {
            Sim->next(NULL);
        } 
        
        // sim->next has to be called, otherwise endless loop !!!
        
    };
    
    R.run(C);
    */
    
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
/*    
   int Nmc   = 1000;
    int depth = 10;
    randUniInt randInt(0,4);
    
    LinkedList<int> Alist; 
    double P[] = {0,20,20,10};
    
    state S = Sim.getState();
    
    cout << S.toString() << endl;
    
    while(!(Sim.EoD())) {
    
        int a = Sim.searchBestAction_MKT_naiveMC(P,1000,30);
        
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

