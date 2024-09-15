#include "Option.h"

Option::~Option() {} // destructeur

Option::Option(double expiry) : _expiry(expiry)
{

} // def du constructeur

double Option::getExpiry() const
{
	return _expiry;
}

double Option::payoffPath(std::vector<double> price)
{
	return payoff(price.back());
}

bool Option::isAsianOption()
{
	return false;
}