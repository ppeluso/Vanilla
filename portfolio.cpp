//
//  portfolio.cpp
//  Vanill
//
//  Created by Peter Peluso on 6/21/16.
//  Copyright © 2016 Peter Peluso. All rights reserved.
//

#include "portfolio.hpp"
#include <vector>
#include "option_pricing.hpp"

Portfolio::Portfolio(double v)
{
    value =v;
    portfolio.push_back(v);
    
    calcVal = 0;
    stock = 0;
    quantity = 0;
    callQuantity = 0;
    callCredit = 0;
    delta = 0;
    pl = 0;
    i = 0;
    l = 0;
}
void Portfolio::setPortfolio(double v)
{
    value =v;
    portfolio[0] = v;
    
    calcVal = 0;
    stock = 0;
    quantity = 0;
    
    
}

void Portfolio::buyStock(double price, double q)
{
    //while((price * q) > value && q > 0 )
    //{
      //  q--;
    //}
    
    //if(q <= 0)
    //{
      //  std::cout<< "not enough capital...no order executed"<<std::endl;
    //}
    //else
    //{
        value -= price * q;
        stock += price *q;
        quantity += q;
        
    //}
    
}
void Portfolio::sellStock(double price, double q)
{
    value += price * q;
    stock  = price *q - stock;
    quantity -= q;
}

double Portfolio::calcValue()
{
    calcVal = value; 
   
    
    return calcVal;
}
double Portfolio::currentValue(double currentPrice, int quant)
{
    return (quant * currentPrice);
    
}

void Portfolio::sellCall( double S, double K, double r,  double v,  double T)
{
    for(int i = 30 ; i  > 0 ; i--)
    {
        if(call_delta(S, (S + i), r, v, T) > 15  )
           {
               K = S +i;
               break;
           }
    }
     
    callCredit += call_price( S,  K,  r,  v,   T) ;
    callAndStrike[callQuantity][0] = call_price( S,  K,  r,  v,   T);
    callAndStrike[callQuantity][1] = K;
    callQuantity++;
} 

double Portfolio::calcDelta(double S, double K, double r,  double v,  double T)
{
    
    while( callAndStrike[i][0] != 0)
    {
        delta += call_delta(S, callAndStrike[i][1],r, v,T);
        
        i++;
    }
    
    delta += quantity;
    
    return delta;
    
}

void Portfolio::rebalanceDelta(double S, double K, double r,  double v,  double T)
{
     l = 0;
    if(calcDelta(S,K,r,v,T) > 15)
    {
        while( calcDelta(S, K, r, v, T) > 15)
        {
            for(int i = 220;  i > 200; i--)
            {
                if(call_delta(S, i, r, v, T)  > 15 )
                {
                    l= i;
                    break;
                }
            }
            sellCall(S,l,r,v,T);
        }
    }
    
    if (calcDelta(S,K,r,v,T) < -15)
    {
        while(calcDelta(S, K, r, v, T) < 0 )
        {
            buyStock(S, 1);
        }
    }
    
}

double Portfolio::buyCall( double S, double K, double r,  double v,  double T)
{
    i = 0;
    pl = 0;
    for( i = 0; i < callQuantity; i++ )
    {
        callCredit = (callCredit- call_price(S,callAndStrike[i][1], r, v, T))*100;
        
       
    }
    
    return callCredit;
}

