#include "VanillaOption.h"
#include <stdexcept>

VanillaOption::VanillaOption(double expiry, double strike) : Option(expiry), _option(strike)
{ // constructeur
    if (expiry < 0 || strike < 0)
    {
        throw std::invalid_argument("expiry and strike should be non-negative");
    }
}

double VanillaOption::getStrike() const
{
    return _option;
}
