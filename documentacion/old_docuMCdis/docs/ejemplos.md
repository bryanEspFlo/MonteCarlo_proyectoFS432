# Ejemplos de uso

### Ejemplo básico

```cpp
#include "MonteCarloMPI.hpp"

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    MonteCarloMPI sim(1000000);
    double vol = sim.ejecutar();

    MPI_Finalize();
}