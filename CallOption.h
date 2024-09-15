#pragma once
#include "VanillaOption.h"

class CallOption : public VanillaOption
{

public:
    CallOption(double expiry, double strike); // constructeur

    OptionType GetOptionType() const override;

    double payoff(double a) override;
};