#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption {
public:
	AsianCallOption(std::vector<double> TimeSteps, double strike);
	double payoff(double a) override;
};

