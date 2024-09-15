#pragma once
#include <iostream>
#include "DigitalOption.h"

class DigitalCallOption : public DigitalOption
{

	public:
		DigitalOptionType GetDigitalOptionType() override {
		return DigitalOptionType::Digitalcall;
		}
		DigitalCallOption(double expiry, double strike);


		double payoff(double a) override;

		~DigitalCallOption();
};
