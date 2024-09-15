#include "BlackScholesMCPricer.h"
#include "MT.h" // bizarre parce que pr�sence de ligne 15 qui devrait suffir
#include <vector>
#include "AsianOption.h"

BlackScholesMCPricer::BlackScholesMCPricer(Option *option, double initial_price, double interest_rate, double volatility) // constructeur
    : _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility)
{
    nbPaths = 0;
    currentPrice = 0;
    meanPayOff = 0;
    Sumpayoff = 0;
}

int BlackScholesMCPricer::getNbPaths()
{
    return nbPaths;
}

void BlackScholesMCPricer::generate(int nb_paths)
{

    int m = 0; // taille
    double expiry = 0;
    double delta = 0;
    std::vector<double> timeSteps;

    if (_option->isAsianOption() == true)
    {
        timeSteps = ((AsianOption*)_option)->getTimeSteps();
        m = timeSteps.size();
        expiry = timeSteps.back();
        delta = expiry / m;
    }
    else // vanilla option
    {
        m = 1;
        expiry = _option->getExpiry();
        delta = expiry / m;
    }

    std::vector<std::vector<double>> comparetable(nb_paths, std::vector<double>()); // PROBLEME JE L'INTIALISE
    double Sumpayoff = 0;
    double meanPayOff = 0;

    for (int i = 0; i < nb_paths; i++)
    {
        comparetable[i].resize(m + 1);
    }

    for (int i = 0; i < nb_paths; i++)
    {
        comparetable[i][0] = _initial_price;
    }
    double N = 0;
    for (int i = 0; i < nb_paths; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            N = MT::rand_norm(gen);
            comparetable[i][j] = comparetable[i][j - 1] * exp(((_interest_rate - ((pow(_volatility, 2) / 2)) * delta) + (_volatility * sqrt(delta) * N)));
        }
        currentPrice = (nbPaths * currentPrice + _option->payoffPath(comparetable[i])) / (nbPaths + 1);
        Sumpayoff = Sumpayoff + (_option->payoffPath(comparetable[i])) * (_option->payoffPath(comparetable[i]));
        nbPaths += 1;
    }
    meanPayOff = currentPrice;
}

double BlackScholesMCPricer::operator()()
{
    if (nbPaths != 0)
    {
        if (_option->isAsianOption() == false)
        {
            return exp(-_interest_rate * _option->getExpiry()) * currentPrice;
        }
        else
        {
            std::vector<double> timeSteps = ((AsianOption*)_option)->getTimeSteps();
            return exp(-_interest_rate * timeSteps.back()) * currentPrice;
        }
    }
    else
    {
        throw std::string("No estimation has been performed thus far; you should first utilize the 'generate' method");
    }
}

std::vector<double> BlackScholesMCPricer::confidenceInterval()
{
    std::vector<double> ConfidenceInt;
    double variance = (1 / (double)nbPaths) * Sumpayoff - meanPayOff * meanPayOff;
    ConfidenceInt.push_back(currentPrice + 1.96 * sqrt((variance / nbPaths)));
    ConfidenceInt.push_back(currentPrice - 1.96 * sqrt((variance / nbPaths)));
    return ConfidenceInt;
}
