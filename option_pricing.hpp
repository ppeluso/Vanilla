//
//  option_pricing.hpp
//  Vanilla
//
//  Created by Peter Peluso on 5/20/16.
//  Copyright © 2016 Peter Peluso. All rights reserved.
//

#ifndef option_pricing_hpp
#define option_pricing_hpp

#include <stdio.h>
double gaussian_box_muller();


double monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);


double monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T);

double norm_pdf(const double x);


double norm_cdf(const double x);

double d_j(const int j, const double S, const double K, const double r, const double v, const double T);


double call_price(const double S, const double K, const double r, const double v, const double T);
double call_delta(const double S, const double K, const double r, const double v, const double T);

double call_gamma(const double S, const double K, const double r, const double v, const double T);

double call_vega(const double S, const double K, const double r, const double v, const double T);

double call_theta(const double S, const double K, const double r, const double v, const double T);

double call_rho(const double S, const double K, const double r, const double v, const double T);


void call(const double S, const double K, const double r, const double v, const double T);


double put_price(const double S, const double K, const double r, const double v, const double T);
double put_delta(const double S, const double K, const double r, const double v, const double T);

double put_gamma(const double S, const double K, const double r, const double v, const double T);

double put_vega(const double S, const double K, const double r, const double v, const double T);


double put_theta(const double S, const double K, const double r, const double v, const double T);


double put_rho(const double S, const double K, const double r, const double v, const double T);


void put(const double S, const double K, const double r, const double v, const double T);


void short_call_spread();


void short_put_spread();

double callImpliedVol( double S, double K, double T, double r, double value);

double putImpliedVol( double S, double K, double T, double r, double value);

#endif /* option_pricing_hpp */

