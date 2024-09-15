#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double assetPrice, double upFactor, double downFactor, double interestRate)
    : _option(option), _depth(depth), _assetPrice(assetPrice), _upFactor(upFactor), _downFactor(downFactor), _interestRate(interestRate) {
    checkForArbitrage();
    _priceTree.setDepth(depth);
}


void CRRPricer::compute() {
    for (int i = 0; i <= _depth; ++i) {
        double stockPrice = _assetPrice * std::pow(1 + _upFactor, i) * std::pow(1 + _downFactor, _depth - i);
        _priceTree.setNode(_depth, i, _option->payoff(stockPrice));
    }
    double riskNeutralProb = (_interestRate - _downFactor) / (_upFactor - _downFactor);
    for (int n = _depth - 1; n >= 0; --n) {
        for (int i = 0; i <= n; ++i) {
            double expectedValue = riskNeutralProb * _priceTree.getNode(n + 1, i + 1) + (1 - riskNeutralProb) * _priceTree.getNode(n + 1, i);
            _priceTree.setNode(n, i, expectedValue / (1 + _interestRate));
        }
    }
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {

        return computeClosedForm();
    }
    else {
        compute();
        return getPrice(); 
    }
}

double CRRPricer::operator()() {
    compute();
    return getPrice();
    
}

double CRRPricer::computeClosedForm() {

    double q = (_interestRate - _downFactor) / (_upFactor - _downFactor);
    double sum = 0.0;
    for (int i = 0; i <= _depth; ++i) {
        double comb = factorial(_depth) / (factorial(i) * factorial(_depth - i));
        double payoff = _option->payoff(_assetPrice * std::pow(1 + _upFactor, i) * std::pow(1 + _downFactor, _depth - i));
        sum += comb * std::pow(q, i) * std::pow(1 - q, _depth - i) * payoff;
    }
    double discountFactor = std::pow(1 + _interestRate, -_depth);
    return discountFactor * sum;
}

double CRRPricer::factorial(int n) const {
    double result = 1.0;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

double CRRPricer::getPrice() const {
    return _priceTree.getNode(0, 0);
}

void CRRPricer::checkForArbitrage() const {
    if (_downFactor >= _interestRate || _interestRate >= _upFactor) {
        throw std::logic_error("Arbitrage opportunity detected");
    }
}

