#include <mpi.h>
#include <cmath>
#include <iostream>
#include <random>
#include <chrono>
#include <cstdint>

double seconds(){
    return MPI_Wtime();
}

int funcIntegrando(double x1, double x2, double x3, double x4){
    return (x1*x1 + x2*x2 + x3*x3 + x4*x4 <= 1.0) ? 1 : 0;
}

double MonteCarlo(int (*func)(double,double,double,double), uint64_t N_global){
    int rank = 0, size = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    uint64_t base = N_global / static_cast<uint64_t>(size);
    uint64_t rem  = N_global % static_cast<uint64_t>(size);
    uint64_t N_local = base + (static_cast<uint64_t>(rank) < rem ? 1ULL : 0ULL);

    uint64_t time_seed = static_cast<uint64_t>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());
    uint64_t seed = time_seed ^ (static_cast<uint64_t>(rank) + 0x9e3779b97f4a7c15ULL);
    std::mt19937_64 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    uint64_t sum_local = 0;

    double t_start = seconds();
    for(uint64_t i = 0; i < N_local; ++i){
        double x1 = dist(rng);
        double x2 = dist(rng);
        double x3 = dist(rng);
        double x4 = dist(rng);
        sum_local += static_cast<uint64_t>( func(x1,x2,x3,x4) );
    }
    double t_end = seconds();
    double time_local = t_end - t_start;

    uint64_t sum_total = 0;
    MPI_Reduce(&sum_local, &sum_total, 1, MPI_UINT64_T, MPI_SUM, 0, MPI_COMM_WORLD);

    double time_max = 0.0;
    MPI_Reduce(&time_local, &time_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    double Integral = 0.0;
    if(rank == 0){
        double pi = std::acos(-1.0);
        double Volumen = (pi * pi) / 2.0;           
        Integral = (16.0 / static_cast<double>(N_global)) * static_cast<double>(sum_total);
        double error = std::fabs(Integral - Volumen) / Volumen;

        std::cout << "Procesos MPI: " << size << std::endl;
        std::cout << "N (global): " << N_global << std::endl;
        std::cout << "Suma dentro de la hiperesfera: " << sum_total << std::endl;
        std::cout << "Integral estimada: " << Integral << std::endl;
        std::cout << "Volumen teorico: " << Volumen << std::endl;
        std::cout << "Error relativo: " << error << std::endl;
        std::cout << "Tiempo (max entre procesos): " << time_max << " s" << std::endl;
        std::cout << std::endl;
    }

    MPI_Bcast(&Integral, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    return Integral;
}

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);

    uint64_t N = 10000000ULL;
    if(argc >= 2){
      try {
        uint64_t tmp = std::stoull(argv[1]); // Usa unsigned long long
        if(tmp > 0) N = tmp;
      } catch (const std::exception& e) {
           std::cerr << "Advertencia: El argumento de entrada no es un número válido o es muy grande. Usando N = " << N << std::endl;
      }
    }

    double result = MonteCarlo(funcIntegrando, N);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank != 0){
        std::cout << "Rank " << rank << " recibió Integral = " << result << std::endl;
    }

    MPI_Finalize();
    return 0;
}
