#pragma once
#include "Option.h"
#include "DigitalOption.h"
#include "VanillaOption.h"

class BlackScholesPricer
{
private:
    VanillaOption *_vanillaOption;
    DigitalOption *_digitalOption;
    double _asset_price;
    double _interest_rate;
    double _volatility;

public:
    BlackScholesPricer(VanillaOption *option, double asset_price, double interest_rate, double volatility);
    BlackScholesPricer(DigitalOption *option, double asset_price, double interest_rate, double volatility);

    double operator()();
    double delta();
    double cdf(double);
};