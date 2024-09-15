#include "AsianCallOption.h"

AsianCallOption::AsianCallOption(std::vector<double> TimeSteps, double strike)  // constructeur
    : AsianOption(TimeSteps, strike) {}

double AsianCallOption::payoff(double a) {
    if (a >= _strike) {
        return a - _strike; // _option 
    }
    else {
        return 0.0;
    }
}