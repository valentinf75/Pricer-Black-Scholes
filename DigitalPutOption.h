#pragma once
#include "DigitalOption.h"

class DigitalPutOption : public DigitalOption
{


public:
	DigitalOptionType GetDigitalOptionType() override {
		return DigitalOptionType::Digitalput;
	}
	~DigitalPutOption();
	

	DigitalPutOption(double expiry, double strike);

	double getExpiry() const;

	double payoff(double a) override;
};
