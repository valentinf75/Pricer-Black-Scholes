#pragma once

#include "Option.h"
#include "BinaryTree.h"

class CRRPricer
{
private:
    Option *_option;
    BinaryTree<double> _priceTree;
    int _depth;
    double _assetPrice;
    double _upFactor;
    double _downFactor;
    double _interestRate;

    void checkForArbitrage() const;

public:
    CRRPricer(Option *option, int depth, double assetPrice, double upFactor, double downFactor, double interestRate);
    void compute();
    double getPrice() const;
    double operator()(bool closed_form);
    double operator()();
    double computeClosedForm();
    double factorial(int n) const;
};
