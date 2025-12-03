#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include "MonteCarloMPI.hpp"

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    long long N = 1000000;
    if (argc >= 2) {
        N = atoll(argv[1]);
    }

    MonteCarloMPI simulacion(N);
    double resultado = simulacion.ejecutar();

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank != 0) {
        std::cout << "Rank " << rank 
                  << ": recibió Integral = " << resultado << std::endl;
    }

    MPI_Finalize();
    return 0;
}