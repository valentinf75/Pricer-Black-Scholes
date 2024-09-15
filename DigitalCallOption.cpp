#include "DigitalCallOption.h"

DigitalCallOption::~DigitalCallOption() {}

DigitalCallOption::DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike) {}



double DigitalCallOption::payoff(double a)
{
	double profit = 0;
	if (a >= getStrike())
		profit = 1;
	return profit;
}