/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef SIMU_H
#define SIMU_H

#include "tools.h"

struct MarketData {
    double** M;
};


struct state {
    double upnl;
    double rpnl;
    int    pos;
    int    holdtime;
    
    //MarketData MD;
};

struct pfEntry {
    int pos;
    double EP;
    int entryHM;
};

class simu {
public:
    simu(IndexedData* data, int firstMin, int posUnit);
    void reset();           // Reset and start @ random day
    void reset(int day);    // Reset and start @ day
    state next(int action); // Next state under action taken
                            // 0: do nothing
                            // 1: go long 
                            // 2: go short
                            // 3: close 
                            // Notes: *In current mechanics, if pos!=0 : 1=2=0.
                            //        *MKT only orders
    
    //state next(int day, int HM, state S, int action); // Optional at the moment, intended for MC planning
    
private:
    IndexedData* Data;
    int N;     // # Elements @ day
    int Day;   // Row pos of day in data
    int r = 0; // Current row pos
   
    int lot; 
    
    double upnl;
    double rpnl;
    
    pfEntry PF;
    
    double commissions(int shares, int type); // Notes:
                                              // (IB fixed| ToDo: Change to tiered, if extended to LMT orders)
                                              // type 0: MKT BUY
                                              // type 1: MKT SELL
                                              // type 2: LMT BUY
                                              // type 3: MKT SELL
                                              
    
};

#endif /* SIMU_H */

