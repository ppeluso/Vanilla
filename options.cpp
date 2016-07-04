#include <Rcpp.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
NumericVector timesTwo(NumericVector x) {
  return x * 2;
}

// [[Rcpp::export]]
double gaussian_box_muller()
{
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;
  
  do
  {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    
    euclid_sq = x*x + y*y;
  }while(euclid_sq >= 1.0);
  
  return x * sqrt(-2*log(euclid_sq)/euclid_sq);
}
// [[Rcpp::export]]
double monte_carlo_call_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  
  for(int i =0; i < num_sims; i++)
  {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(S_cur - K, 0.0);
    
  }
  
  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
  
  
}
// [[Rcpp::export]]
double monte_carlo_put_price(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T)
{
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;
  
  for (int i=0; i<num_sims; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(K - S_cur, 0.0);
  }
  
  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}
// [[Rcpp::export]]
double norm_pdf(const double x)
{
  return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
  
}
// [[Rcpp::export]]
double norm_cdf(const double x)
{
  double k;
  k = 1.0/(1.0+0.2316419*x);
  double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));
  if (x >= 0.0) {
    return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
  } else {
    return 1.0 - norm_cdf(-x);
  }
}
// [[Rcpp::export]]
double d_j(const int j, const double S, const double K, const double r, const double v, const double T)
{
  return (log(S/K) + (r+(pow(-1,j-1)) *0.5*v*v)*T)/(v*(pow(T,0.5)));
  
}
// [[Rcpp::export]]
double call_price(const double S, const double K, const double r, const double v, const double T)
{
  return S * norm_cdf(d_j(1,S,K,r,v,T))-K*exp(-r*T)*norm_cdf(d_j(2,S,K,r,v,T));
}
// [[Rcpp::export]]
double call_delta(const double S, const double K, const double r, const double v, const double T)
{
  return norm_cdf(d_j(1,S,K,r,v,T));
}
// [[Rcpp::export]]
double call_gamma(const double S, const double K, const double r, const double v, const double T)
{
  return norm_pdf(d_j(1,S,K,r,v,T))/(S*v*sqrt(T));
}
// [[Rcpp::export]]
double call_vega(const double S, const double K, const double r, const double v, const double T)
{
  return S*norm_pdf(d_j(1,S,K,r,v,T))*sqrt(T);
}
// [[Rcpp::export]]
double call_theta(const double S, const double K, const double r, const double v, const double T)
{
  return -(S*norm_pdf(d_j(1, S, K, r, v, T))*v)/(2*sqrt(T))
  - r*K*exp(-r*T)*norm_cdf(d_j(2, S, K, r, v, T));
  
}
double call_rho(const double S, const double K, const double r, const double v, const double T)
{
  return K*T *exp(-r*T)*norm_cdf(d_j(2,S,K,r,v,T));
}
// [[Rcpp::export]]
void call(const double S, const double K, const double r, const double v, const double T)
{
  std::cout << "Price of call option: " << call_price(S,K,r,v,T)<< '\n';
  std::cout << "Delta: " << call_delta(S,K,r,v,T)<< '\n';
  std::cout << "Gamma: " << call_gamma(S,K,r,v,T)<< '\n';
  std::cout << "Vega: " << call_vega(S,K,r,v,T)<< '\n';
  std::cout << "Theta: " << call_theta(S,K,r,v,T)<< '\n';
  std::cout << "Rho: " << call_rho(S,K,r,v,T)<< '\n';
  std::cout << "\nPrice using Monte Carlo Method: " << monte_carlo_call_price(1000000,S,K,r,v,T);
  
}
// [[Rcpp::export]]
double put_price(const double S, const double K, const double r, const double v, const double T) {
  return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}
// [[Rcpp::export]]
double put_delta(const double S, const double K, const double r, const double v, const double T) {
  return norm_cdf(d_j(1, S, K, r, v, T)) - 1;
}
// [[Rcpp::export]]
double put_gamma(const double S, const double K, const double r, const double v, const double T) {
  return call_gamma(S, K, r, v, T); // Identical to call by put-call parity
}
// [[Rcpp::export]]
double put_vega(const double S, const double K, const double r, const double v, const double T) {
  return call_vega(S, K, r, v, T); // Identical to call by put-call parity
}

// [[Rcpp::export]]
double put_theta(const double S, const double K, const double r, const double v, const double T) {
  return -(S*norm_pdf(d_j(1, S, K, r, v, T))*v)/(2*sqrt(T))
  + r*K*exp(-r*T)*norm_cdf(-d_j(2, S, K, r, v, T));
}

// [[Rcpp::export]]
double put_rho(const double S, const double K, const double r, const double v, const double T)
{
  return -T*K*exp(-r*T)*norm_cdf(-d_j(2, S, K, r, v, T));
}
// [[Rcpp::export]]
void put(const double S, const double K, const double r, const double v, const double T)
{
  std::cout << "Price of Put option: " << put_price(S,K,r,v,T)<< '\n';
  std::cout << "Delta: " << put_delta(S,K,r,v,T)<< '\n';
  std::cout << "Gamma: " << put_gamma(S,K,r,v,T)<< '\n';
  std::cout << "Vega: " << put_vega(S,K,r,v,T)<< '\n';
  std::cout << "Theta: " << put_theta(S,K,r,v,T)<< '\n';
  std::cout << "Rho: " << put_rho(S,K,r,v,T)<< '\n';
  std::cout << "\nPrice using Monte Carlo Method: " << monte_carlo_put_price(1000000,S,K,r,v,T);
  
}
// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
timesTwo(42)
*/
