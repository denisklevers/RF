/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef SIMU_H
#define SIMU_H

#include "tools.h"
#include <string>

struct MarketData {
    double** M;
};

struct pfEntry {
    int pos;
    double EP;
    int entryHM;
};


struct state {
    int r; // Current row pos (as offset of Day)
    
    double upnl;
    double rpnl;
   
    pfEntry PF;
    
    //MarketData MD;
    
    std::string toString() {
        std::string s = "[S] r: "+std::to_string(r)
                       +" pos: "+std::to_string(PF.pos)
                       +" upnl: "+std::to_string(upnl)
                       +" rpnl: "+std::to_string(rpnl);
        
        return s;
    }
};


class simu {
public:
    simu(IndexedData* data, int firstMin, int posUnit);
    void reset();           // Reset and start @ random day
    void reset(int day, int firstMin); // Reset and start @ day
    state next(int action); // Next state under action taken
                            // 0: do nothing
                            // 1: go long 
                            // 2: go short
                            // 3: close 
                            // Notes: *In current mechanics, if pos!=0 : 1=2=0.
                            //        *MKT only orders
    
    bool EoD();             // Returns TRUE if end-of-day reached
    
    state next(state S, int action); // Takes S as current state and jumps to day offset r therein and executes action
    
private:
    IndexedData* Data;
    int N;     // # Elements @ day
    int Day;   // Row pos of day in data
    int lot;   // lot size to use
 
    state S;
    
    double commissions(int shares, int type); // Notes:
                                              // (IB fixed| ToDo: Change to tiered, if extended to LMT orders)
                                              // type 0: MKT BUY
                                              // type 1: MKT SELL
                                              // type 2: LMT BUY
                                              // type 3: MKT SELL
                                              
    
};

#endif /* SIMU_H */

