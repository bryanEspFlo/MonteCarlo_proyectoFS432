#include "MonteCarloMPI.hpp"
#include <random>
#include <cmath>
#include <iostream>

/**
 * @brief Determina si un punto pertenece a la hiperesfera 4D de radio 1.
 *
 * Se evalúa la condición:
 *   x1^2 + x2^2 + x3^2 + x4^2 <= 1
 *
 * @return 1 si el punto pertenece a la hiperesfera, 0 en caso contrario.
 */
int MonteCarloMPI::funcIntegrando(double x1, double x2, double x3, double x4) {
    return sqrt((x1*x1 + x2*x2 + x3*x3 + x4*x4 <= 1.0)) ? 1 : 0;
}

/**
 * @brief Constructor que inicializa la cantidad global y local de muestras.
 *
 * Calcula cuántos puntos corresponden al proceso mediante una división equitativa.
 */
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

/**
 * @brief Ejecuta el método de Monte Carlo distribuido mediante MPI.
 *
 * Implementa:
 * - Generador aleatorio simple por proceso.
 * - Conteo de puntos dentro de la hiperesfera.
 * - Reducción de la suma total mediante MPI_Reduce.
 * - Cálculo del volumen (proceso 0).
 * - Envío del resultado a todos los procesos con MPI_Bcast.
 *
 * @return Valor de la integral estimada (volumen aproximado).
 */
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
