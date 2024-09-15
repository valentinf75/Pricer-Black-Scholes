#pragma once
#include "Option.h"

class BlackScholesMCPricer
{
private:
    Option *_option;
    double _initial_price;
    double _interest_rate;
    double _volatility;
    int nbPaths;
    double currentPrice;
    double meanPayOff;
    double Sumpayoff;

public:
    BlackScholesMCPricer(Option *option, double initial_price, double interest_rate, double volatility);

    int getNbPaths();

    void generate(int);

    double operator()();

    std::vector<double> confidenceInterval();
};
