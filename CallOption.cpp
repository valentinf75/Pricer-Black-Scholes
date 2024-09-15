#include "CallOption.h"

CallOption::CallOption(double expiry, double strike) // constructeur
    : VanillaOption(expiry, strike)
{
}

OptionType CallOption::GetOptionType() const
{
    return OptionType::call;
}

double CallOption::payoff(double a)
{
    if (a >= getStrike())
    {
        return a - getStrike(); // je sais pas si le GetStrike marche vrmt dans ce sens
    }
    else
    {
        return 0.0;
    }
}
