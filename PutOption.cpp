#include "PutOption.h"

PutOption::PutOption(double expiry, double strike)
    : VanillaOption(expiry, strike) {}

OptionType PutOption::GetOptionType() const
{
    return OptionType::put;
}
double PutOption::payoff(double a)
{
    if (a <= getStrike())
    {
        return getStrike() - a;
    }
    else
    {
        return 0.0;
    }
}