/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simu.h
 * Author: krefl
 *
 * Created on September 28, 2016, 8:57 PM
 */

#ifndef SIMU_H
#define SIMU_H

struct MarketData {
    double** M;
};


struct state {
    double upnl;
    double rpnl;
    int    pos;
    int    holdtime;
    
    MarketData MD;
};


struct pfEntry {
    int pos;
    double EP;
    int entryHM;
};

class simu {
public:
    simu();
    void reset();           // Reset and start @ random day 9:30
    state next(int action); // Next state under action taken
    state next(int day, int HM, state S, int action); // Optional at the moment, intended for MC planning
    
private:
    double upnl;
    double rpnl;
    
    pfEntry PF;
};

#endif /* SIMU_H */

