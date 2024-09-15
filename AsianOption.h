#pragma once

#include "Option.h"
#include <vector>
class AsianOption : public Option {
private:
    std::vector<double> _TimeSteps; // attribut priv�
    double _strike;

public:
    AsianOption(std::vector<double> TimeSteps, double strike);
    std::vector<double> getTimeSteps() const;
    double payoffPath(std::vector<double>) override;
    bool isAsianOption() override;
    friend class AsianCallOption;
    friend class AsianPutOption;
};


