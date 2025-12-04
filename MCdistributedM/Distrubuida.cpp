#include "Distribuida.hpp"
#include <mpi.h>
#include <iostream>
#include <cmath>

MonteCarloMPI::MonteCarloMPI(long long N)
    : N_global(N), dist(-1.0, 1.0)
{
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    unsigned seed = rank + 1;
    rng = std::default_random_engine(seed);
}

int MonteCarloMPI::integrando(double x1, double x2, double x3, double x4) {
    double r2 = x1*x1 + x2*x2 + x3*x3 + x4*x4;
    return (r2 <= 1.0) ? 1 : 0;
}

double MonteCarloMPI::ejecutar() {

    long long base = N_global / size;
    long long extra = (rank < (N_global % size)) ? 1 : 0;
    long long N_local = base + extra;

    long long sum_local = 0;

    double t0 = MPI_Wtime();
    for(long long i = 0; i < N_local; i++) {
        double x1 = dist(rng);
        double x2 = dist(rng);
        double x3 = dist(rng);
        double x4 = dist(rng);

        sum_local += integrando(x1, x2, x3, x4);
    }
    double t1 = MPI_Wtime();

    long long sum_total = 0;
    MPI_Reduce(&sum_local, &sum_total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double local_time = t1 - t0;
    double time_max = 0;

    MPI_Reduce(&local_time, &time_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    double Integral = 0.0;

    if(rank == 0){
        double pi = acos(-1.0);
        double Volumen = (pi*pi)/2.0;

        Integral = (16.0 * sum_total) / (double)N_global;
        double error = fabs(Integral - Volumen) / Volumen;

        std::cout << "\nProcesos MPI: " << size << std::endl;
        std::cout << "N global: " << N_global << std::endl;
        std::cout << "Puntos dentro: " << sum_total << std::endl;
        std::cout << "Volumen estimado: " << Integral << std::endl;
        std::cout << "Volumen teorico: " << Volumen << std::endl;
        std::cout << "Error relativo: " << error << std::endl;
        std::cout << "Tiempo max: " << time_max << " s\n" << std::endl;
    }

    MPI_Bcast(&Integral, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    return Integral;
}

