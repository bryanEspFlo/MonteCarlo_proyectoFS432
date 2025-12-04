

# Class MonteCarloMPI



[**ClassList**](annotated.md) **>** [**MonteCarloMPI**](classMonteCarloMPI.md)



_Clase que implementa el método de Monte Carlo distribuido mediante MPI._ [More...](#detailed-description)

* `#include <Distribuida.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MonteCarloMPI**](#function-montecarlompi) (long long N\_total) <br>_Constructor que inicializa la simulación y asigna trabajo local._  |
|  double | [**ejecutar**](#function-ejecutar) () <br>_Ejecuta la simulación Monte Carlo distribuida._  |




























## Detailed Description


Cada proceso MPI genera una cantidad asignada de puntos aleatorios y evalúa si estos pertenecen a la hiperesfera de radio 1 en 4 dimensiones. Los resultados se combinan mediante una reducción para obtener la estimación final. 


    
## Public Functions Documentation




### function MonteCarloMPI 

_Constructor que inicializa la simulación y asigna trabajo local._ 
```C++
MonteCarloMPI::MonteCarloMPI (
    long long N_total
) 
```



Constructor que inicializa la cantidad global y local de muestras.


Divide de manera equilibrada el total de muestras entre los procesos, asignando una muestra adicional a los primeros procesos si N\_global no es divisible de forma exacta por el número de procesos.




**Parameters:**


* `N_total` Número global de muestras.

Calcula cuántos puntos corresponden al proceso mediante una división equitativa. 


        

<hr>



### function ejecutar 

_Ejecuta la simulación Monte Carlo distribuida._ 
```C++
double MonteCarloMPI::ejecutar () 
```



Ejecuta el método de Monte Carlo distribuido mediante MPI.


Este método:
* Genera puntos aleatorios dentro del intervalo [-1,1].
* Evalúa el integrando para cada punto.
* Usa MPI\_Reduce para sumar los resultados.
* Calcula el volumen aproximado (solo en el proceso 0).
* Difunde el valor final a todos los procesos con MPI\_Bcast.






**Returns:**

Valor estimado del volumen de la hiperesfera.


Implementa:
* Generador aleatorio simple por proceso.
* Conteo de puntos dentro de la hiperesfera.
* Reducción de la suma total mediante MPI\_Reduce.
* Cálculo del volumen (proceso 0).
* Envío del resultado a todos los procesos con MPI\_Bcast.






**Returns:**

Valor de la integral estimada (volumen aproximado). 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/Distribuida.hpp`

