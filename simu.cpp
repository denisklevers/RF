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

    reset();

    S.r  = firstMin; // First active time in day
    
}

void simu::reset() {
    S.PF.pos, S.PF.entryHM, S.PF.EP = 0;
    S.r, S.upnl, S.rpnl = 0;
   
    intint d = *Data->index.random();
    Day = d.A;
    N   = d.B;
}

void simu::reset(int day, int firstMin) {
    S.PF.pos, S.PF.entryHM, S.PF.EP = 0;
    S.upnl, S.rpnl = 0;
    S.r = firstMin;
    
    intint d = *Data->index.get(day);
    Day = d.A;
    N   = d.B;
    
}

bool simu::EoD() {
    return S.r >= N;
}

state simu::next(state S_in, int action) {
    S = S_in;
    
    // Check if r is in range, if not set to last possible one (close)
    if(S.r+1 >=N) {
        S.r = N-1;
    }
    
    return next(action);
}

state simu::next(int action) {
   
    // Init new state to return
    state Sn;
    
    Sn.rpnl = S.rpnl;
    Sn.r = S.r+1;
    Sn.PF.EP = S.PF.EP;
    Sn.PF.entryHM = S.PF.entryHM;
    Sn.PF.pos = S.PF.pos;
    
    // Generate new market data for agent
    //...
    
    
    // Check if EoD reached
    if(S.r==N-1) {
        action = 3;
    }
    
    if(S.r==N) {
        return S;
    }
    
    // Perform action
    switch(action) {
        case 0: break;
        // Go long
        case 1: if(S.PF.pos==0) {
                    Sn.PF.pos = lot;
                    Sn.PF.entryHM = S.r;
                    Sn.PF.EP = Data->data[Day+S.r][3]; // Pick up current ASK price 
                    
                    Sn.rpnl -= commissions(Sn.PF.pos, 0);
                    
                } 
                break;
        // Go short
        case 2: if(S.PF.pos==0) {
                    Sn.PF.pos = -lot;
                    Sn.PF.entryHM = S.r;
                    Sn.PF.EP = Data->data[Day+S.r][6]; // Pick up current BID price 
                    
                    Sn.rpnl -= commissions(abs(Sn.PF.pos), 1);
                }
                break;
        // Close
        case 3: if(S.PF.pos!=0) {
                    
                    if(S.PF.pos >= 0) {
                        Sn.rpnl += S.PF.pos*(Data->data[Day+S.r][6] - S.PF.EP);
                    } else {
                        Sn.rpnl += S.PF.pos*(Data->data[Day+S.r][3] - S.PF.EP);
                    }
                
                    int f = (S.PF.pos >= 0) ? 1 : 0; 
             
                    Sn.rpnl -= commissions(S.PF.pos, f);
                    
                    Sn.PF.pos  = 0;
                    Sn.upnl = 0;
                }
                
    }
    
    // Calc upnl
    Sn.upnl = Sn.PF.pos*(Data->data[Day+S.r][3] - Sn.PF.EP);
   
    S = Sn;
    
    return S;
}

double simu::commissions(int shares, int type) {
    
    return std::max(shares*0.005,1.0);
}