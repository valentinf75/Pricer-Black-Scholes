#ifndef MT_H
#define MT_H

#include <random>

class MT {
private:
    std::mt19937 generator; 

    MT(); // constructeur privé

public:
    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    static MT& getInstance();

    static std::mt19937 gen;

    static double rand_unif(std::mt19937);
    static double rand_norm(std::mt19937);

    friend class BlackScholesMCPricer;
};

#endif 

