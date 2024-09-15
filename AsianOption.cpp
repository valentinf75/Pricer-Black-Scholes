#include "AsianOption.h"

AsianOption::AsianOption(std::vector<double> TimeSteps, double strike) : Option(TimeSteps.back())
{
    _TimeSteps = TimeSteps;
    _strike = strike;
}

std::vector<double> AsianOption::getTimeSteps() const
{
    return _TimeSteps;
}

double AsianOption::payoffPath(std::vector<double> price)
{
    int size = price.size();
    double sum = 0;

    for (int i = 1; i < size; i++)
    {
        sum = sum + price[i];
    }

    return payoff((1 / size) * sum);
}

bool AsianOption::isAsianOption()
{
    return true;
}
