/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runner.cpp
 * Author: Dan
 * 
 * Created on October 22, 2016, 7:49 PM
 */

#include "Runner.h"
#include <string>
#include <thread>
#include <iostream>
#include <time.h>

Runner::Runner(int cores, std::string dataPath) {
    // Init threads
    N_cores = cores;
    status = new coreStatus[N_cores];
    
    for(int t = 0; t < N_cores; t++) {
        status[t] = available;
    }
    
    // Load data
    std::cout << "Loading data... ";
    std::string file = dataPath+"/NY_M_AMZN_USD.csv";
   
    data = loadAndIndexDataFromCSV(file.data(), 152100, 10, 1, 1); // ToDo: Automatic discovery of Nr, Nc
    std::cout << data->toString() << std::endl;
    
    // Init simulators
    simulators = new simu[N_cores];
    
    for(int c = 0; c < N_cores; c++) {
        simulators[c] = simu(data, 60, 5000, 0.85, 5); // ToDo: get parameters as arguments
    }
} 

void Runner::run(std::function<void(simu*)> func) { // Do via Lambda expression ?!?
    
    arr<int> keys = data->index.getKeySet();
    
    int p = 0;
    
    do {     
        // Wait for available core
        int core = -1;
        while((core = nextCore()) < 0) {
            wait(100);
        }
        
        
        // Start thread on free core
        status[core] = busy;
        std::thread T(&Runner::runThread, this, core, keys[p], func);
        T.detach();
        std::cout << "T["+std::to_string(core)+"]: started ("+std::to_string(keys[p])+")\n";
      
        p++;
        
    } while( p < keys.size() );
     
    // Wait until all threads are finished before
    while(!threadsFinishedQ()) {
        wait(100);
    }
    
    
}


void Runner::runThread(int core, int key, std::function<void(simu*)> func) {//int* core, int* pos) {
    
    simulators[core].reset(key, 0); // ToDo: FirstMin shift
    
    simu s = simulators[core];
    
    while(!s.EoD()) {
    
        func(&s);
    
        //std::cout << "T["+std::to_string(core)+"]:"+s.getState().toString()+"\n";
    }
    
    std::cout << "T["+std::to_string(core)+"]:"+s.getState().toString()+"\n";
    
    // free core
    std::cout << "T["+std::to_string(core)+"]: finished\n";
    status[core] = available;  
    
}

int Runner::nextCore() {
    
    for(int c = 0; c < N_cores; c++) {
        if(status[c] == available) return c;
    }
    
    return -1;
}    
    
bool Runner::threadsFinishedQ() {
    
    for(int c = 0; c < N_cores; c++) {
        if(status[c] == busy) return false;
    }
    
    return true;
}

