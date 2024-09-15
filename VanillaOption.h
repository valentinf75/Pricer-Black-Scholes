#pragma once

#include "Option.h"

class VanillaOption : public Option
{
private:
    double _option; // attribut priv�

public:
    VanillaOption(double expiry, double strike); // constructeur

    virtual OptionType GetOptionType() const = 0; // la m�thode virtuelle GetOptionType
    double getStrike() const;
    friend class BlackScholesPricer;
};
