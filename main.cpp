//
//  main.cpp
//  Vanill
//
//  Created by Peter Peluso on 6/21/16.
//  Copyright © 2016 Peter Peluso. All rights reserved.
//
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "option_pricing.hpp"
#include "portfolio.hpp"
#include "function.hpp"
#include <string>

#include <fstream>

/* ---------------To Do -----------------------
 - Fix date problem 
 - Clear array 
 - Get this motherfucker to run!!!
 
 
 --------------------------------------------*/
int main()
{
    std::vector<double> dataValue;
    std::vector<double>dataQuantity;
    
    std::vector<std::string> line;
    std::vector<std::string> line2;
    
    std::string a;
    std::vector<double> spy_close; // 2.1.1993 - 6.23.2016
    std::vector<double> spy_open;
    std::vector<double> vix_close;
    std::vector<double> implied_vol;
    std::vector<double> pl;
    std::vector<double> q_num;
    std::string q;
    double y;
    double stockPrice;
    
    
    Portfolio myPortfolio(10000);
    


// /* -------------------Getting Data into vector------------------------- *
//     std::ifstream in;
//     in.open("YAHOO-INDEX_SPY.csv");
//     std::string value;
//     while ( in.good() )
//     {
//         getline ( in, value, ',' );
//         line.push_back(value);
    
//     }
//     for ( int i = 10; i < line.size()-1; i+=6)
//     {
//         q = line[i];
        
//         y =  std::stod(q);
        
//         spy_close.push_back(y);
        
//     }
//     for ( int i = 7; i < line.size()-1; i+=6)
//     {
//         q = line[i];
        
//         y =  std::stod(q);
        
//         spy_open.push_back(y);
        
//     }
    
//     in.close();
    
    
//     std::ofstream myfile;
//     myfile.open ("five.csv");
//     myfile << "Current Value,Quantity,S&P \n";
//     std::ifstream vix;
//     vix.open("CBOE-VIX.csv");
    
//     while ( vix.good() )
//     {
//         getline ( vix, value, ',' );
//         line2.push_back(value);
        
       
        
//     }
    
//     for(int i = 12; i < line2.size(); i += 4)
//     {
//         q = line2[i];
        
//         y =  std::stod(q);
        
//         vix_close.push_back(y);
//         implied_vol.push_back((y/100));
        
//     }
    
//     vix.close();
    
    
// /*------------------------------------------------------------------------*/
//      int xx = 365;
    
//     myPortfolio.sellCall(100, 10, .02, implied_vol.at(10), .20);
    
//     std::cout<< myPortfolio.buyCall(100, 10, .02, implied_vol.at(10), .01);
    
    
   
//     for(int month = 0; month < 12; month++)
//     {
    
//         //myPortfolio.callCredit = 0;
//         //myPortfolio.callQuantity = 0;
        
        
        
       
        
//         for(int day = 28 ; day > 0; day--)
//         {
//             myPortfolio.buyStock(spy_open.at(xx), 1);
//            // myPortfolio.rebalanceDelta(spy_open.at(xx), 0, .02, implied_vol.at(xx), day/252);
            
//             //pl.push_back(myPortfolio.currentValue(spy_open.at(xx), myPortfolio.quantity) + myPortfolio.buyCall(spy_open.at(xx), 10, .02, implied_vol.at(xx)/252, day/252));
            
//             pl.push_back(myPortfolio.currentValue(spy_close[xx], myPortfolio.quantity)+myPortfolio.calcValue());
//             q_num.push_back(myPortfolio.quantity);
            
//             xx--;
//         }
        
//         for(int i = 0; i < 2000; i++)
//         {
//             myPortfolio.callAndStrike[i][0] = 0;
//             myPortfolio.callAndStrike[i][1] = 0;
//         }
        
//     }
    
  
    
//     for(int i = 0; i < pl.size()-1; i++)
//     {
//        // dataQuantity[i] = myPortfolio.quantity;
        
//         myfile << pl.at(i)<<","<<q_num.at(i)<<","<<spy_open[pl.size() - i]<<"\n";
        
        
//     }
//     myfile.close();
    
//  /*
//     myPortfolio.sellCall(100, 110, .05, .2, 1);
//     myPortfolio.sellCall(100, 104, .05, .2, .5);
   
//     std::cout<<call_price(100, 110, .05, .2, 1)<<std::endl;
//     std::cout<<call_price(100, 104, .05, .2, .5)<<std::endl;
//     std::cout<<myPortfolio.callCredit<<std::endl; 
//     std::cout<<call_price(103, 110, .05, .2, .02)<<std::endl;
//     std::cout<<call_price(103, 104, .05, .2, .02)<<std::endl;

//     std::cout<< myPortfolio.buyCall(103, 110, .05, .2, .02)<<std::endl;

//    */

impliedVolSmile(49.28, 50.00, .017, 14.0/252.0, 1, 'C', "hff");
    return 0;
}

    

