/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include "simu.h"
#include <cstdio>
#include <cstdlib>

simu::simu(IndexedData* data, int firstMin, int posUnit) {
    Data = data;
    lot  = posUnit;
    r    = firstMin; // First active time in day
    
    reset();
}

void simu::reset() {
    upnl,rpnl = 0;
    PF.pos = 0;
    PF.EP = 0;
    PF.entryHM = 0;
    
    intint d = *Data->index.random();
    Day = d.A;
    N   = d.B;
}

void simu::reset(int day) {
    upnl,rpnl = 0;
    PF.pos = 0;
    PF.EP = 0;
    PF.entryHM = 0;
  
    intint d = *Data->index.get(day);
    Day = d.A;
    N   = d.B;
}

state simu::next(int action) {
    
    // Check if EoD reached
    if(r==N-1) {
        action = 3;
    }
    
    // Perform action
    switch(action) {
        case 0: break;
        // Go long
        case 1: if(PF.pos==0) {
                    PF.pos = lot;
                    PF.entryHM = r;
                    PF.EP = Data->data[Day+r][3]; // Pick up current ASK price 
                    
                    rpnl -= commissions(lot, 0);
                    
                } 
                break;
        // Go short
        case 2: if(PF.pos==0) {
                    PF.pos = -lot;
                    PF.entryHM = r;
                    PF.EP = Data->data[Day+r][6]; // Pick up current BID price 
                    
                    rpnl -= commissions(lot, 1);
                }
                break;
        // Close
        case 3: if(PF.pos!=0) {
                    
                    if(PF.pos >= 0) {
                        rpnl += Data->data[Day+r][6] - PF.EP;
                    } else {
                        rpnl += -1*(Data->data[Day+r][3] - PF.EP);
                    }
                
                    int f = (PF.pos >= 0) ? 1 : 0; 
             
                    rpnl -= commissions(lot, f);
                    
                    PF.pos  = 0;
                    upnl = 0;
                }
                
    }
    // Generate new state to return
    state S;
    S.holdtime = 0;
    
    // Calc upnl
    if(PF.pos!=0) {
        S.holdtime = r - PF.entryHM;
        
        if(PF.pos > 0) {
            upnl = (Data->data[Day+r][3] - PF.EP);
            
        } else {
            upnl = -1*(Data->data[Day+r][3] - PF.EP);
        }
    }
    
    S.pos = PF.pos;
    S.rpnl = rpnl;
    S.upnl = upnl;
    
    // Generate market data for agent
    //...
    
    // Increase row counter
    r++;
    
    return S;
}

double simu::commissions(int shares, int type) {
    
    return std::max(shares*0.005,1.0);
}