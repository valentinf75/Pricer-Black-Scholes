#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption {
public:
	AsianPutOption(std::vector<double> TimeSteps, double strike);
	double payoff(double a) override;
};
