//
//  function.cpp
//  Vanill
//
//  Created by Peter Peluso on 6/25/16.
//  Copyright © 2016 Peter Peluso. All rights reserved.
//

#include "function.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "option_pricing.hpp"
#include "portfolio.hpp"
#include <fstream>

void zeroArr(double a[])
{
    for(int i = 0; i < 2000-1; i++)
    {
        a[i] = 0;
        
    }
}
