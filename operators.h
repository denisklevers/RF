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





}
#endif /* OPERATORS_H */

