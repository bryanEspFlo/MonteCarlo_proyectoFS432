# Cálculo del volumen de una hiperesfera en 4D con MC en memoria compartida

A continuación se presentanta un ejemplo de uso del método de Monte Carlo para el cálculo de integrales.
En este caso se calculó el volumen de una hiperesfera en 4 dimenciones. 
Con este propósito, se realizó un programa en C++ con programación orientada a objetos en memoria distribuida.

## Uso

Primero se debe crear un objeto de tipo MC e indicar el número de iteraciones que se desea realizar.
Luego, para calcular el volumen se invoca el método .calcInt(). 
Para conocer el resultado obtenido y el error cometido se invocan los métodos .getIntVal() y .getErrVal().

```cpp
MC MC1(10000000);
MC1.calcInt();
std::cout << MC1.getIntVal() << std::endl;
std::cout << MC1.getErrVal() << std::endl;
```
El código anterior arroja el siguiente resultado:

```cpp
>>> 4.93
>>> 0.002
```

## Compilación

Para compilar se deben tener los archivos: MCsharem.hpp con la declaración de la clase, MCshareme.cpp con 
la implementación de la clase y main.cpp. Después, se compilan los archivos con la extensión .cpp utilizando
g++ y también colocando -fopenmp al final de la línea.

Una vez compilado el código necesario, se ejecuta: export OMP\_NUM\_THREADS=N (con N el número de hilos) para parallelizar el proceso.
Por último, se ejecuta el archivo main.cpp.
