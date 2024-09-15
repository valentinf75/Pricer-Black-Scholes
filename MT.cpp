#include "MT.h"

std::random_device rd;
std::mt19937 MT::gen(rd());

MT::MT() {}

double MT::rand_unif(std::mt19937 random) {
    std::uniform_real_distribution<double> udistrib(0.0, 1.0);
    return udistrib(random);
}

double MT::rand_norm(std::mt19937 random) {
    std::normal_distribution<double> ndistrib(0.0, 1.0);
    return ndistrib(random);
}

MT& MT::getInstance()
{
    static MT instance;
    return instance;
}
