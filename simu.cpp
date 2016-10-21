/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



#include "simu.h"
#include <cstdio>
#include <cstdlib>
#include "tools.h"


int simu::searchBestAction_MKT_naiveMC(double penalties[], int depth, int runs) 
{
    // Set reward counter
    double R[4] = {0,0,0,0};
 
    // Save current state:
    state S_init = getState();
    
    // Vars
    int nac[2] = {1,2};
    order O    = {0,1,0};
            
    // MC runs
    for(int m = 0; m < runs; m++) {
        
        setState(S_init);
        
        int r;
        
        if(S.PF.pos==0) {
            r = randInt.nextSkip(3);
        } else {
            r = randInt.nextSkip(nac, 2);
        }
        
        O.action = r;
        
        // MC depth run
        for(int i = 0; i < depth; i++) {
            // Generate and execute random order
            state S = next(&O);
            O.action = randInt.next();
        }
            
        state T = getState();
        
        R[r] += T.upnl+T.rpnl;
        
        // Command penalty;
        R[r] -= penalties[r];
    }
    
       
    // Cleanup 
    setState(S_init);
    
    int a;
   
    if(S.PF.pos==0) {
        a = posOfFirstMax(R, 4, 3); 
    } else {
        a = posOfFirstMax(R, 4, nac, 2);
    }
    
    return a;
}


simu::simu(IndexedData* data, int firstMin, double posValue, double fillRate) {
    Data = data;
    invSize = posValue;
    CF   = coinFlipper(fillRate);
    
    reset(firstMin);
 
}

void simu::reset(int firstMin) {
   
    intint d = *Data->index.random();
    Day = d.A;
    N   = d.B;
    
    S.day = Day;
    S.r = Day+firstMin;    
    
}

void simu::reset(int day, int firstMin) {
    
    intint d = *Data->index.get(day);
    Day = d.A;
    N   = d.B;
    
    S.day = Day;
    S.r   = Day+firstMin;   
}

state simu::getState() {
    return S;
}

void simu::setState(state in) {
    S = in;
}

bool simu::EoD() {
    return S.r-Day >= N;
}

state simu::next(state S_in, order* O) {
    S = S_in;
    
    // Check if r is in range, if not set to last possible one (close)
    if(S.r-Day+1 >=N) {
        S.r = Day+N-1;
    }
    
    return next(O);
}

bool simu::processOrder(order* Oin, state* Sin) {

    if(Oin!=NULL && Sin!=NULL) {
        if(Oin->lifetime >= 0) {
            
            // Check if filled long (LMT)
            if(     Oin->action == 1
                &&  Oin->LMT    >  0
                &&  Sin->PF.pos == 0
                && (    Oin->LMT > Data->data[Sin->r][5]  // min ASK broke through LMT, definite fill 
                    || (Oin->LMT == Data->data[Sin->r][5] && CF.coinFlip()) // min ASK reaches LMT, fill with probability p
                   ) 
              )
            {
                Sin->PF.pos = Oin->pos;
                Sin->PF.entryHM = Sin->r-Day;
                Sin->PF.EP = Oin->LMT; 
                
                Sin->rpnl -= commissions(abs(Oin->pos), abs(Oin->pos)*Oin->LMT, 0, true);
                
                return true;
            }
            
            // Check if filled long (MKT)
            if(     Oin->action == 1
                &&  Oin->LMT    == 0
                &&  Sin->PF.pos == 0
              )
            {
                Sin->PF.pos = Oin->pos;
                Sin->PF.entryHM = Sin->r-Day;
                Sin->PF.EP = Data->data[Sin->r-1][4]; // Take previous ASK (time of order send) 
                
                Sin->rpnl -= commissions(abs(Oin->pos), abs(Oin->pos)*Sin->PF.EP, 0, false);
                
                return true;
            }
            
            // Check if filled short
            if(     Oin->action == 2 
                &&  Oin->LMT    >  0
                &&  Sin->PF.pos == 0    
                && (    Oin->LMT < Data->data[Sin->r][8]  // min BID broke through LMT, definite fill 
                    || (Oin->LMT == Data->data[Sin->r][8] && CF.coinFlip()) // min BID = LMT, fill with probability p
                   ) 
              )
            {
                Sin->PF.pos = Oin->pos;
                Sin->PF.entryHM = S.r-Day;
                Sin->PF.EP = Oin->LMT;
                    
                Sin->rpnl -= commissions(abs(Oin->pos), abs(Oin->pos)*Oin->LMT, 1, true);  
                
                return true;
            }
           
            // Check if filled short (MKT)
            if(     Oin->action == 2
                &&  Oin->LMT    == 0
                &&  Sin->PF.pos == 0
              )
            {
                Sin->PF.pos = Oin->pos;
                Sin->PF.entryHM = Sin->r-Day;
                Sin->PF.EP = Data->data[Sin->r-1][7]; // Take previous ASK (time of order send) 
                
                Sin->rpnl -= commissions(abs(Oin->pos), abs(Oin->pos)*Sin->PF.EP, 0, false);
                
                return true;
            }
            
            // Check if close order filled (LMT))
            if(     Oin->action == 3 
                &&  Oin->LMT     > 0
                &&  Sin->PF.pos != 0
              ) 
            
            {
                if(Sin->PF.pos > 0) {
                    if(     Oin->LMT < Data->data[Sin->r][8]  // BID broke through LMT, definite fill 
                        || (Oin->LMT == Data->data[Sin->r][8] && CF.coinFlip()) // BID = LMT, fill with probability p
                      ) 
                    {
                       Sin->rpnl += Sin->PF.pos*(Oin->LMT - Sin->PF.EP) - commissions(abs(Sin->PF.pos), abs(Sin->PF.pos)*Oin->LMT, 1, true);
                       
                       Sin->PF.pos = 0;
                       Sin->PF.entryHM = 0;
                       Sin->PF.EP = 0;
                       
                       return true;
                    }
                } else {
                    if(
                            Oin->LMT > Data->data[Sin->r][5]  // ASK broke through LMT, definite fill 
                        || (Oin->LMT == Data->data[Sin->r][5] && CF.coinFlip()) // ASK = LMT, fill with probability p
                      )
                    {
                        Sin->rpnl += Sin->PF.pos*(Oin->LMT - Sin->PF.EP) - commissions(abs(Sin->PF.pos), abs(Sin->PF.pos)*Oin->LMT, 0, true);
                     
                        Sin->PF.pos = 0;
                        Sin->PF.entryHM = 0;
                        Sin->PF.EP = 0;
                     
                        return true; 
                    } 
                }
            } 
            
            // Check if close order filled (MKT))
            if(     Oin->action == 3 
                &&  Oin->LMT    == 0
                &&  Sin->PF.pos != 0
              ) 
            
            {
                if(Sin->PF.pos > 0) {
                    double P = Data->data[Sin->r-1][4];
                    
                    Sin->rpnl += Sin->PF.pos*(P - Sin->PF.EP) - commissions(abs(Sin->PF.pos), abs(Sin->PF.pos)*P, 1, false);
                       
                    Sin->PF.pos = 0;
                    Sin->PF.entryHM = 0;
                    Sin->PF.EP = 0;
                       
                    return true;
                   
                } else {
                    double P = Data->data[Sin->r-1][7];
                  
                    Sin->rpnl += Sin->PF.pos*(P - Sin->PF.EP) - commissions(abs(Sin->PF.pos), abs(Sin->PF.pos)*P, 0, false);
                     
                    Sin->PF.pos = 0;
                    Sin->PF.entryHM = 0;
                    Sin->PF.EP = 0;
                     
                    return true; 
                }
            }  
            
            Oin->lifetime--;  
        } 
    }

    return false;
}

state simu::next(order* O) {
    
    // Check if EoD reached (close on MID)
    if(S.r==Day+N-1) {
        
        if(S.PF.pos!=0) {
            S.rpnl += S.PF.pos*((Data->data[S.r][4]+Data->data[S.r][7])/2 - S.PF.EP) - commissions(abs(S.PF.pos), abs(S.PF.pos)*(Data->data[S.r][4]+Data->data[S.r][7])/2, 0, 0);
                     
            S.PF.pos = 0;
            S.PF.entryHM = 0;
            S.PF.EP = 0;
        }
        
        S.AO = NULL;
        O = NULL;
    }
  
    if(S.r==Day+N) {
        return S;
    }
    
    // Init new state to return
    state Sn;
    
    Sn.rpnl       = S.rpnl;
    Sn.day        = S.day;
    Sn.r          = S.r+1;
    Sn.PF.EP      = S.PF.EP;
    Sn.PF.entryHM = S.PF.entryHM;
    Sn.PF.pos     = S.PF.pos;
   
    // Process old (stored) order (if present)
    if(S.AO!=NULL && S.AO->lifetime <= 0) {
        S.AO = NULL;
    }
    
    Sn.AO = (processOrder(S.AO, &Sn)) ? NULL : S.AO;
    
    // Set new order if present (cancels old)
    if(O!=NULL) {
        
        if(   O->action == 4       // Cancel command
           || (    O->action == 3  
                && Sn.PF.pos == 0  // Invalid order
              )
           || (   (O->action == 1||O->action == 2)
                && Sn.PF.pos != 0  // Invalid order
              )
           || ( O->action == 0)  // Invalid order
          )
        {
            // Cancel order (due to command)
               Sn.AO = NULL;
        } else {
            
            // Set pos size 
            if(O->action == 3) {
                O->pos = S.PF.pos;
            }
            
            if((O->action == 1 || O->action == 2)) {
                O->pos = calc_shares();
            }
            
            Sn.AO = O;
        }  
    } 
    
    // Process new order (if present)
    Sn.AO = (processOrder(Sn.AO, &Sn)) ? NULL : Sn.AO;
    
    // Calc MID upnl (use Sn MID)
    Sn.upnl = Sn.PF.pos*((Data->data[Sn.r][4]+Data->data[Sn.r][7])/2 - Sn.PF.EP);
    Sn.upnl_p = Sn.upnl/invSize;
    
    //  Calc rpnl_p
    Sn.rpnl_p = Sn.rpnl/invSize;
    
    // Set state
    S = Sn;
    
    return S;
}

int simu::calc_shares() {
   return floor(invSize/((Data->data[S.r][4]+Data->data[S.r][7])/2));   
} 

double simu::commissions(int shares, double value, int type, bool LMT) {
    
    double Cs = std::min(std::max(0.0035*shares,0.35),value*0.05); // IB commissions
    Cs += Cs*(0.000175+0.00056); // Pass-through fees
    Cs += (LMT) ? -1*shares*0.0014 : shares*0.00275; // NYSE fees
    Cs += shares*0.00020; // Clearing fees
    Cs += (type==0) ? 0.0 : 0.0000218*value+0.000119*shares; // Transaction fee
            
    return Cs;
}