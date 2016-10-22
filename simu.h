/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#ifndef SIMU_H
#define SIMU_H

#include "tools.h"
#include "FiniteQueue.h"
#include <string>

using namespace tools;


struct pfEntry {
    int pos, entryHM;
    double EP;    
};

struct order {
    int action;
    int pos;
    int lifetime;
    double LMT;
    
    std::string toString() {
        std::string s = "[O] a: "+std::to_string(action)
                       +" l: "+std::to_string(lifetime)
                       +" LMT: "+std::to_string(LMT);
        
        return s;
    }
};

struct simuLog {
    FiniteQueue<int>*    actions;
    FiniteQueue<double>* upnls;
    FiniteQueue<double>* rpnls;

};

struct state {
    int day; // Row pos of day;
    int r;   // Current absolute row pos
    
    double upnl, upnl_p, rpnl, rpnl_p; 
    
    pfEntry PF;
    order* AO;
    
    std::string toString() {
        std::string s = "[S] d: "+std::to_string(day)
                       +" r:"+std::to_string(r-day)
                       +" pos: "+std::to_string(PF.pos)
                       +" upnl: "+std::to_string(upnl)
                       +" upnl_p: "+std::to_string(upnl_p)
                       +" rpnl: "+std::to_string(rpnl)
                       +" rpnl_p: "+std::to_string(rpnl_p);
             
        if(AO!=NULL) {
            s += "\n "+AO->toString();
        }
        
        return s;
    }
};




class simu {
public:
    simu(IndexedData* data, int firstMin, double posValue, double fillRate, int logSize);
    
    void reset(int firstMin);          // Reset and start @ random day
    void reset(int day, int firstMin); // Reset and start @ day
    
    state next(order* O); // Next state under action taken
                            // 0: do nothing (OR simply NULL pointer in)
                            // 1: go long 
                            // 2: go short
                            // 3: close 
                            // 4: Cancel order
                            // Notes: *In current mechanics, if pos!=0 : 1=2=0.
                            //        *MKT only orders
    
                            // ToDo: Add flip pos order ...
    
    bool EoD();             // Returns TRUE if end-of-day reached
    
    state next(state S, order* O); // Takes S as current state and jumps to day offset r therein and executes action
    
    state getState();
    void  setState(state S);
    
    int calc_shares();
    
    int searchBestAction_MKT_naiveMC(double penalties[], int depth, int runs);
    
    simuLog* getLog() {
        return &L;
    }
    
private:
    IndexedData* Data;
    
    int N;     // # Elements @ day
    int Day;   // Row pos of day in data
   
    double invSize;
    
    state S = {};
    
    coinFlipper CF      = NULL; // To determine if LMT order @ LMT gets filled / min
    randUniInt  randInt = randUniInt(0,3); // Random uniform number generator (for MC command runs)
    
    simuLog L = {}; 
    bool log = true;
    
    bool processOrder(order* Oin, state* Sin); // Returns true if Oin filled
    
    /*
     * Calculates commissions for order 
     * (based on IB fees)
     *
     * type 0: BUY
     * type 1: SELL
     * 
     * LMT  0: MKT order
     *      1: LMT order
     */
    double commissions(int shares, double value, int type, bool LMT); 
    
};

#endif /* SIMU_H */

