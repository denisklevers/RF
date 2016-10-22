/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   operators.h
 * Author: Dan
 *
 * Created on October 18, 2016, 11:45 PM
 */

#ifndef OPERATORS_H
#define OPERATORS_H

#include "tools.h"

namespace ops {
    
/*
 * Operator base class defs
 * 
 */
class vec_op 
{
public:
    virtual arr<double> apply(arr<double>) = 0;
    virtual ~vec_op() {};
};

class sca_op 
{
public:
    virtual double apply(arr<double>) = 0;
    virtual ~sca_op() {};
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Vector operators
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*
 * % change over step size
 * 
 * step : step size
 * 
 */
class d_p : public vec_op
{
public:
    d_p(int step) {
        S = step;
    }
    
    virtual arr<double> apply(arr<double> in) 
    {
        return tools::d_p(in, S);
    }
    
private:
    int S;
};

/*
 * Simple moving average 
 * 
 * wlength : window length
 *
 */
class sma : public vec_op
{
public:
    
    sma(int wlength) {
        W = wlength;
    }
    
    virtual arr<double> apply(arr<double> in) 
    {
        double* data = new double[in.size-W+1];
        
        // Calc moving average
        for(int i = W-1; i < in.size; i++) {
            
            // Calc mean
            double m = 0;
            for(int w = i-W+1; w <= i; w++) {
                m += in[w];
            }
            
            data[i-W+1] = m/W;
        }
        
        return {data, in.size-W+1};
    }
    
private:
    int W;
};


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Scalar operators
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
 * Mean
 * 
 */
class mean : public sca_op 
{
    virtual double apply(arr<double> in) {
        return tools::mean(in).x;
    }
};

/*
 * Standard deviation
 * 
 */
class sdev : public sca_op 
{
    virtual double apply(arr<double> in) {
        return tools::mean(in).y;
    }
};

/*
 * Sum over elements
 *
 */
class sum : public sca_op 
{
    virtual double apply(arr<double> in) {
        return tools::sum(in);
    }
};

/*
 * Min of elements
 *
 */
class min : public sca_op
{
    virtual double apply(arr<double> in) {
        return tools::min(in);
    }
};

/*
 * Max of elements
 *
 */
class max : public sca_op
{
    virtual double apply(arr<double> in) {
        return tools::max(in);
    }
};


/*
 * Auto-correlation
 *
 */
class acorr : public sca_op 
{
    acorr(int lag) {
        L = lag;
    }
    
    virtual double apply(arr<double> in) {
        return tools::autoCorrelation(in, L);
    }
    
private:
    int L;
};



}
#endif /* OPERATORS_H */

