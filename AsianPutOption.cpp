#include "AsianPutOption.h"

AsianPutOption::AsianPutOption(std::vector<double> TimeSteps, double strike)  // constructeur
    : AsianOption(TimeSteps, strike) {}

double AsianPutOption::payoff(double a) {
    if (a <= _strike) {
        return _strike - a;
    }
    else {
        return 0.0;
    }
}
