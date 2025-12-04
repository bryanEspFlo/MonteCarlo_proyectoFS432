

# File Distribuida.hpp

[**File List**](files.md) **>** [**include**](dir_d44c64559bbebec7f509842c48db8b23.md) **>** [**Distribuida.hpp**](Distribuida_8hpp.md)

[Go to the documentation of this file](Distribuida_8hpp.md)


```C++
/* @brief Declaración de la clase MonteCarloMPI para cálculo del volumen de una hiperesfera
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

class MonteCarloMPI {
private:
    long long N_global;   
    long long N_local;    
    int rank;             
    int size;             

    int funcIntegrando(double x1, double x2, double x3, double x4);

public:

    MonteCarloMPI(long long N_total);

    double ejecutar();
};

#endif // MONTECARLOMPI_HPP
```


