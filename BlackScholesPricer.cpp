#include "BlackScholesPricer.h"
#include <cmath>

BlackScholesPricer::BlackScholesPricer(VanillaOption *vanillaOption, double asset_price, double interest_rate, double volatility)
    : _vanillaOption(vanillaOption), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility)
{
    _digitalOption = 0;
}

BlackScholesPricer::BlackScholesPricer(DigitalOption *digitalOption, double asset_price, double interest_rate, double volatility)
    : _digitalOption(digitalOption), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility)
{
    _vanillaOption = 0;
}

double BlackScholesPricer::cdf(double value)
{
    return 0.5 * std::erfc(-value / std::sqrt(2));
}

double BlackScholesPricer::operator()()
{
    double K ;
    double T ;
    double d1;
    double d2;
    double r = _interest_rate;
    double S = _asset_price;
    double sigma = _volatility;


    if (_digitalOption == 0)
    {
        K = _vanillaOption -> getStrike();
        T = _vanillaOption ->getExpiry();
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        
        if (_vanillaOption->getOptionType() == OptionType::call)
        {
            double callPrice = S * cdf(d1) - K * std::exp(-r * T) * cdf(d2);
            return callPrice;
        }
        else
        {
            double putPrice = K * std::exp(-r * T) * cdf(-d2) - S * cdf(-d1); // a voir probleme de signe avec d2 et d1
            return putPrice;
        }
    }
    else
    {
        K = _digitalOption ->getStrike();
        T = _digitalOption ->getExpiry();
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        d2 = (std::log(S / K) + (r - 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
        
        if (_digitalOption->GetDigitalOptionType() == DigitalOptionType::Digitalcall)
        {
            double callPrice = S * cdf(d1) - K * std::exp(-r * T) * cdf(d2);
            return callPrice;
        }
        else
        {
            double putPrice = K * std::exp(-r * T) * cdf(-d2) - S * cdf(-d1); // a voir probleme de signe avec d2 et d1
            return putPrice;
        }
    }
}

double BlackScholesPricer::delta()
{
    double K ;
    double T ;
    double d1;
    double r = _interest_rate;
    double S = _asset_price;
    double sigma = _volatility;
    
    
    if (_digitalOption == 0)
    {
        K = _vanillaOption -> getStrike();
        T = _vanillaOption ->getExpiry();
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        if(_vanillaOption -> getOptionType() == OptionType::call)
        {
            return cdf(d1);
        }
        else
        {
            return cdf(d1) - 1 ;
        }

    }
    else
    {
        K = _digitalOption ->getStrike();
        T = _digitalOption ->getExpiry();
        d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

        if(_digitalOption -> GetDigitalOptionType() == DigitalOptionType::Digitalcall)
        {
            return cdf(d1);
        }
        else
        {
            return cdf(d1) - 1 ;
        }
    }
    
    
}
