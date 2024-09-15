#include "DigitalPutOption.h"

DigitalPutOption::~DigitalPutOption() {}

DigitalPutOption::DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) {}



double DigitalPutOption::payoff(double a)
{
	double profit = 0;
	if (a <= getStrike())
		profit = 1;
	return profit;
}