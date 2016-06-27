//
//  portfolio.hpp
//  Vanilla
//
//  Created by Peter Peluso on 6/21/16.
//  Copyright © 2016 Peter Peluso. All rights reserved.
//

#ifndef portfolio_hpp
#define portfolio_hpp

#include <stdio.h>
#include <vector>
#include "option_pricing.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "portfolio.hpp"


class Portfolio {
private:
    
public:
    Portfolio(double v);
    
    void setPortfolio(double v);
    
    void buyStock(double price, double q);
    
    void sellStock(double price, double q);
    
    double calcValue();
    
    void EOD();
    
    double value;
    
    std::vector <double> portfolio;
    
    double stock;
    
    int quantity;
    
    double calcVal;
    double currentValue(double currentPrice, int quant);
    
    void sellCall( double S,  double K,  double r,  double v, double T);
    
    double callCredit;
    
    int callQuantity;
    
    double callAndStrike[2000][2];
    
    double delta;
    int i;
    int l;
    double pl; 
    
    double calcDelta(double S, double K, double r,  double v,  double T);
    
    void rebalanceDelta(double S, double K, double r,  double v,  double T);
    
    double buyCall( double S, double K, double r,  double v,  double T);
    
    
};




#endif /* portfolio_hpp */