

# Class MC



[**ClassList**](annotated.md) **>** [**MC**](classMC.md)



_Clase_ [_**MC**_](classMC.md) _(Monte Carlo) que calcula integrales con el método homónimo._[More...](#detailed-description)

* `#include <MCsharem.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**N**](#variable-n)  <br>_Cantidad de iteraciones para realizar Monte Carlo._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MC**](#function-mc-22) (int N) <br>_Constructor personalizado de la clase_ [_**MC**_](classMC.md) _._ |
|  void | [**calcInt**](#function-calcint) () <br>_Método que calcula el volumen de la hiperesfera con Monte carlo._  |
|  double | [**getErrVal**](#function-geterrval) () const<br>_Devuelve el error cometido al calcular la integral._  |
|  double | [**getIntVal**](#function-getintval) () const<br>_Devuelve el valor de la integral calculada con Monte Carlo._  |
|  double | [**getNVal**](#function-getnval) () const<br>_Devuelve la cantidad de iteraciones realizadas._  |
|  double | [**getTime**](#function-gettime) () const<br>_Devuelve el tiempo que se toma en calcular la integral con Monte Carlo._  |




























## Detailed Description


La clase [**MC**](classMC.md) permite calcular el volumen de una hiperesfera unitaria en 4 dimenciones. 


    
## Public Attributes Documentation




### variable N 

_Cantidad de iteraciones para realizar Monte Carlo._ 
```C++
int MC::N;
```




<hr>
## Public Functions Documentation




### function MC [2/2]

_Constructor personalizado de la clase_ [_**MC**_](classMC.md) _._
```C++
MC::MC (
    int N
) 
```



Constructor personzalizado de la clase [**MC**](classMC.md).




**Parameters:**


* `N` Atributo con la cantidad de interaciones. 




        

<hr>



### function calcInt 

_Método que calcula el volumen de la hiperesfera con Monte carlo._ 
```C++
void MC::calcInt () 
```



Calcula la integral para saber el volumen de la hiperesfera con Monte Carlo. 


        

<hr>



### function getErrVal 

_Devuelve el error cometido al calcular la integral._ 
```C++
double MC::getErrVal () const
```



Devuelve el error cometido del calculo de la integral. 


        

<hr>



### function getIntVal 

_Devuelve el valor de la integral calculada con Monte Carlo._ 
```C++
double MC::getIntVal () const
```




<hr>



### function getNVal 

_Devuelve la cantidad de iteraciones realizadas._ 
```C++
double MC::getNVal () const
```




<hr>



### function getTime 

_Devuelve el tiempo que se toma en calcular la integral con Monte Carlo._ 
```C++
double MC::getTime () const
```



@ brief Devuelve que toma el cálculo de la integral con Monte Carlo. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `include/MCsharem.hpp`

