#Cálculo del volumen de una hiperesfera en 4D con MC en memoria distribuida (MPI)

A continuación se presenta un ejemplo de uso del método de Monte Carlo para el cálculo de integrales.
En este caso se calcula el volumen de una hiperesfera en 4 dimensiones.
Con este propósito, se realizó un programa en C++ orientado a objetos utilizando memoria distribuida mediante MPI.

##Uso

Primero se debe crear un objeto de tipo MonteCarloMPI, indicando el número total de iteraciones que se desea realizar.
Luego, para calcular el volumen se invoca el método .ejecutar().

El proceso rank 0 mostrará el volumen estimado, el volumen teórico, el error relativo y el tiempo máximo de ejecución entre todos los procesos.

El siguiente ejemplo utiliza la clase con MPI:

Primero se debe crear un objeto de tipo MonteCarloMPI, indicando el número total de iteraciones que se desea realizar.
Luego, para calcular el volumen se invoca el método .ejecutar().

El proceso rank 0 mostrará el volumen estimado, el volumen teórico, el error relativo y el tiempo máximo de ejecución entre todos los procesos.

El siguiente ejemplo utiliza la clase con MPI:

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    long long N = 10000000;
    MonteCarloMPI MC(N);

    double volumen = MC.ejecutar();

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        std::cout << "Volumen calculado: " << volumen << std::endl;
    }

    MPI_Finalize();
    return 0;
}

##Compilación

Para compilar se deben tener los archivos:

MonteCarloMPI.hpp — declaración de la clase
MonteCarloMPI.cpp — implementación de la clase
main.cpp — archivo principal que usa la clase

Luego, se compilan utilizando mpic++:

mpic++ -O2 -o MonteCarlo main.cpp MonteCarloMPI.cpp

##Ejecución

ara ejecutar el programa con N procesos se utiliza:

mpirun -np N ./MonteCarlo

Por ejemplo, con 8 procesos:

mpirun -np 8 ./MonteCarlo