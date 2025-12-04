* @brief Declaración de la clase MonteCarloMPI para cálculo del volumen de una hiperesfera
 *        en 4 dimensiones mediante el método de Monte Carlo con paralelismo MPI.
 *
 * La clase encapsula el proceso completo:
 * - División del número global de muestras entre procesos.
 * - Generación de puntos aleatorios dentro del hipercubo [-1,1]^4.
 * - Evaluación del integrando para determinar si el punto cae dentro de la hiperesfera.
 * - Reducción de resultados con MPI.
 * - Cálculo del volumen estimado.
 */

#ifndef MONTECARLOMPI_HPP
#define MONTECARLOMPI_HPP

#include <mpi.h>

/**
 * @class MonteCarloMPI
 * @brief Clase que implementa el método de Monte Carlo distribuido mediante MPI.
 *
 * Cada proceso MPI genera una cantidad asignada de puntos aleatorios y evalúa si
 * estos pertenecen a la hiperesfera de radio 1 en 4 dimensiones. Los resultados se
 * combinan mediante una reducción para obtener la estimación final.
 */
class MonteCarloMPI {
private:
    long long N_global;   ///< Número total de puntos a generar entre todos los procesos.
    long long N_local;    ///< Número de puntos asignados a este proceso.
    int rank;             ///< Identificador del proceso MPI.
    int size;             ///< Cantidad total de procesos MPI.

    /**
     * @brief Función integrando que determina si un punto pertenece a la hiperesfera 4D.
     *
     * @param x1 Coordenada x1 del punto.
     * @param x2 Coordenada x2 del punto.
     * @param x3 Coordenada x3 del punto.
     * @param x4 Coordenada x4 del punto.
     * @return 1 si el punto está dentro de la hiperesfera, 0 en caso contrario.
     */
    int funcIntegrando(double x1, double x2, double x3, double x4);

public:

    /**
     * @brief Constructor que inicializa la simulación y asigna trabajo local.
     *
     * Divide de manera equilibrada el total de muestras entre los procesos,
     * asignando una muestra adicional a los primeros procesos si N_global no
     * es divisible de forma exacta por el número de procesos.
     *
     * @param N_total Número global de muestras.
     */
    MonteCarloMPI(long long N_total);

    /**
     * @brief Ejecuta la simulación Monte Carlo distribuida.
     *
     * Este método:
     * - Genera puntos aleatorios dentro del intervalo [-1,1].
     * - Evalúa el integrando para cada punto.
     * - Usa MPI_Reduce para sumar los resultados.
     * - Calcula el volumen aproximado (solo en el proceso 0).
     * - Difunde el valor final a todos los procesos con MPI_Bcast.
     *
     * @return Valor estimado del volumen de la hiperesfera.
     */
    double ejecutar();
};

#endif // MONTECARLOMPI_HPP