#include "DigitalOption.h"

DigitalOption::~DigitalOption() {}

DigitalOption::DigitalOption(double expiry, double strike) : Option(expiry)
{
	if (strike >= 0)
		_option = strike;
	else
		throw std::out_of_range("Incorrect");
}
double DigitalOption::getStrike() const
{
	return _option;
}


