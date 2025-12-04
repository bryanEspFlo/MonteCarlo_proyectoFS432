# Cálculo del volumen de una hiperesfera en 4D con MC en memoria compartida

A continuación se presentan un ejemplo de uso del método de Monte Carlo para el cálculo de integrales.
En este caso se calcula el volumen de una hiperesfera en 4 dimenciones. 
Con este propósito, se realizó un programa en C++ orientado a objetos en memoria distribuida.

## Uso

Primero se debe crear un objeto de tipo *MC* e indicar el número de iteraciones que se desea realizar.
Luego, para calcular el volumen se invoca el método *.calcInt()*. 
Para conocer el resultado obtenido y el error cometido se invocan los métodos *.getIntVal()* y *.getErrVal()*.

El siguiente código se realizó con un hilo.

```cpp
MC MC1(10000000);
MC1.calcInt();
std::cout << MC1.getIntVal() << std::endl;
std::cout << MC1.getTime() << std::endl;
std::cout << MC1.getErrVal() << std::endl;
```
El código anterior arroja el siguiente resultado:

```cpp
>>> 4.93608
>> 5.97295
>>> 0.000259909
```

## Compilación

Para compilar se deben tener los archivos: *MCsharem.hpp* con la declaración de la clase, *MCshareme.cpp* con 
la implementación de la clase y *main.cpp*. Después, se compilan los archivos con la extensión *.cpp* utilizando
*g++* y también colocando *-fopenmp* al final de la línea.

Una vez compilado el código necesario, se ejecuta: *export OMP\_NUM\_THREADS=N* (con N el número de hilos) para paralelizar el proceso.
Por último, se ejecuta el archivo *main.cpp* el cual contiene el uso que se quiera hacer de la clase *MC*.
