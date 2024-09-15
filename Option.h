#pragma once

#include <vector>

enum class OptionType {call, put};

class Option
{
private:
    double _expiry; // argument privée de Option

protected:
    OptionType type;

public:
    Option(double expiry);

    ~Option();

    double getExpiry() const;

    OptionType getOptionType() const { return type; }

    virtual double payoff(double) = 0; // une méthode virtuelle pure dans la classe Option
    virtual double payoffPath(std::vector<double>);

    virtual bool isAsianOption();

    friend class BlackScholesPricer; // ami pour avoir GetExpiry dans BSPricer
    friend class BlackScholesMCPricer;
};
