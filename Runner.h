/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Runner.h
 * Author: Dan
 *
 * Created on October 22, 2016, 7:49 PM
 */

#ifndef RUNNER_H
#define RUNNER_H

#include "simu.h"
#include <string>
#include <thread>

enum coreStatus {
    available,
    busy
};

class Runner {
public:
    Runner(int cores=1, std::string dataPath="");

    void run(std::function<void(simu*)> func);
    
private:
    
    int N_cores;
    
    IndexedData* data = NULL;
    simu* simulators  = NULL;
    
    coreStatus* status = NULL;
    
    int nextCore();
    
    void runThread(int core, int key, std::function<void(simu*)> func);
    bool threadsFinishedQ();
};

#endif /* RUNNER_H */

