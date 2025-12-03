#ifndef MONTECARLOMPI_HPP
#define MONTECARLOMPI_HPP

#include <random>

class MonteCarloMPI {
private:
    int rank;               
    int size;               
    long long N_global;     

    std::default_random_engine rng;
    std::uniform_real_distribution<double> dist;

public:
    MonteCarloMPI(long long N);

    int integrando(double x1, double x2, double x3, double x4);
    double ejecutar();
};

#endif