

# File Distribuida.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**Distribuida.cpp**](Distribuida_8cpp.md)

[Go to the documentation of this file](Distribuida_8cpp.md)


```C++
#include "MonteCarloMPI.hpp"
#include <random>
#include <cmath>
#include <iostream>

int MonteCarloMPI::funcIntegrando(double x1, double x2, double x3, double x4) {
    return sqrt((x1*x1 + x2*x2 + x3*x3 + x4*x4 <= 1.0)) ? 1 : 0;
}

MonteCarloMPI::MonteCarloMPI(long long N_total) {
    N_global = N_total;

    // Obtenemos información del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // División equitativa entre procesos
    long long base = N_global / size;
    long long extra = (rank < (N_global % size)) ? 1 : 0;
    N_local = base + extra;
}

double MonteCarloMPI::ejecutar() {

    // Generador aleatorio sencillo basado en el rank
    std::default_random_engine rng(rank + 1);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    long long sum_local = 0;

    // Tiempo local del proceso
    double t0 = MPI_Wtime();
    for(long long i = 0; i < N_local; i++){
        double x1 = dist(rng);
        double x2 = dist(rng);
        double x3 = dist(rng);
        double x4 = dist(rng);

        sum_local += funcIntegrando(x1, x2, x3, x4);
    }
    double t1 = MPI_Wtime();

    long long sum_total = 0;

    // Suma total de puntos dentro de la hiperesfera en todos los procesos
    MPI_Reduce(&sum_local, &sum_total, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // Recopilación del tiempo máximo
    double time_local = t1 - t0, time_max = 0.0;
    MPI_Reduce(&time_local, &time_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    double Integral = 0.0;

    // Solo el proceso 0 calcula y muestra la información final
    if(rank == 0){
        double pi = std::acos(-1.0);
        double VolumenTeorico = (pi * pi) / 2.0;

        // Volumen estimado mediante Monte Carlo
        Integral = 16.0 * sum_total / (double)N_global;

        std::cout << "\n==== Resultados Monte Carlo MPI ====\n";
        std::cout << "Puntos dentro de la hiperesfera: " << sum_total << "\n";
        std::cout << "Volumen estimado: " << Integral << "\n";
        std::cout << "Volumen teórico: " << VolumenTeorico << "\n";
        std::cout << "Error relativo: "
                  << std::fabs(Integral - VolumenTeorico) / VolumenTeorico << "\n";
        std::cout << "Tiempo máximo MPI: " << time_max << " s\n";
        std::cout << "====================================\n";
    }

    // Se difunde el resultado final a todos los procesos
    MPI_Bcast(&Integral, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    return Integral;
}
```


