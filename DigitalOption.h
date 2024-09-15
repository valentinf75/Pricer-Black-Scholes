#pragma once

#include <iostream>
#include "Option.h"

enum class DigitalOptionType
{
	Digitalcall,
	Digitalput
};

class DigitalOption : public Option
{

private:
	double _option;

public:
	~DigitalOption();

	virtual DigitalOptionType GetDigitalOptionType() = 0;

	DigitalOption(double expiry, double strike);

	double getStrike() const;

	friend class BlackScholesPricer;
};
