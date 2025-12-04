# Cálculo del volumen de una hiperesfera con el método de Monte Carlo
 
El método de Monte Carlo para el cálculo de integrales es particularmente útil cuando se trabaja en muchas dimenciones.
Para mostrar el uso de esta metodología, a continuación se presentan dos implementaciónes de la integración de Monte Carlo en C++
paralelizando el proceso.
 
* [Código de las implementaciones](https://github.com/bryanEspFlo/MonteCarlo_proyectoFS432)


## Integración de Monte Carlo

La integración de Monte Carlo utiliza métodos probabilísticos para calcular integrales a trevés del uso de números aleatorios.
Existen varias formas de la integración de Monte Carlo, por ejemplo, el método estándar aproxima la integral al delimitar
la región en la que se encuetra la función a integrar y calculando la probabilidad de que puntos aleatorios estén en la región 
de la integral, aproximando la integral de la siguiente forma.

\begin{align}
I \approx \frac{kA}{N}
\end{align}

Donde $I$ es la integral, $k$ el número de puntos dentro de la región de la integral y $N$ la cantidad de puntos.

Otra forma de la integración de Monte Carlo y aún más eficiente, es el *método del valor intermedio*, el cual
es el que se implementa para los códigos de las implementaciones que aquí se exponen.

En el *método del valor intermedio* se define el valor promedio de una función de la siguiente forma.

\begin{align}
f_{prom} = \frac{1}{b-a} \int_{a}^{b} {\rm{d}}x f(x) = \frac{I}{b-a}
\end{align}

\begin{align}
I = (b-a)f_{prom}
\end{align}

Entonces, conociendo el valor promedio de la función, se puede saber el valor de la integral $I$; una forma de saberlo es 
utilizando números aleatorios de la siguiente forma.

\begin{align}
\frac{1}{N} \sum_{i=1}^{N} f(x_{i})
\end{align}

\begin{align}
I = \frac{b-a}{N} \sum_{i=1}^{N} f(x_{i})
\end{align}

Donde $x_{i}$ corresponden a puntos aleatorios uniformemente distribuidos. 

El error cometido en ambas formas de la integración de Monte Carlo está dado por un factor $\frac{1}{\sqrt{N}}$.

## Aceleración de la integración de Monte Carlo

Generar números aleatorios es en general costoso, por lo que, en la práctica, se utilizan algoritmos que generan números
con un comportamiento cercano a uno aleatorio, es decir, se utilizan *números pseudoaleatorios*. En los códigos de la 
implementación se utiliza el módulo `std::uniform_real_distribution` de la biblioteca *random* para generar
los números pseudoaleatorios.

Se utiliza el paralelismo de memoria distrubuida y compartida para acelerar el proceso del cálculo de la integración de 
Monte Carlo, en este caso, para calcular el volumen de una hiperesfera en 4 dimenciones debido a que existe una fórmula 
general para su volumen en cualquier dimención. Para una hiperesfera unitara de 4 dimenciones, se tiene que su volumen es de **4.935**.

Para la paralelización del trabajo en memoria compartida, se distribuye el trabajo utilizando *OpenMP*. La paralelización se realiza
en el cálculo de la sumatoria en el método del punto medio al divir los índices entre los hilos utilizados. Similarmente,
también se implementa la integración con el método del punto medio al distribuir el cálculo en procesos utilizando el estandar de
*Intel MPI*.

**Referencia**

Mark, N. Computational Physics. University of Michigan; 2013.
