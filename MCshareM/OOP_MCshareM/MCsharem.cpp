#include <iostream>
#include <cmath>
#include "MCsharem.hpp"
#include <random>
#include <omp.h>
#include <sys/time.h>

MC::MC(int num_N){ // Constructor personalizado.
  N = num_N;
  valorIntegral = 0.0;
  valorError = 0.0;
} 
  
// Método con la función para el cálculo del volumen de una esfera en 4D.
int MC::Esphere4D(double x1, double x2, double x3, double x4){
   int val_func = 0;
  
   if(sqrt(x1*x1 + x2*x2 + x3*x3 + x4*x4) <= 1){
     val_func = 1;
   }
  
  return val_func;
}


// Método para calcular el tiempo en que tardan las iteraciones.
double MC::seconds(){
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0; 
  return sec;
}


// Método que calcula una integral utilizando Monte Carlo.
void MC::calcInt(){

  int sumatoria = 0;
  int num_procesos;
 
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
 
  // Paralelización del cálculo de la sumatoria.
  double t_inicial = seconds();
  #pragma omp parallel
  {
   num_procesos = omp_get_num_threads();
 
   #pragma omp for reduction(+: sumatoria)
   for(int i = 0; i < N; i++){
      sumatoria += Esphere4D(distribution(generator), distribution(generator),
                             distribution(generator), distribution(generator));
    }
  }
  double t_final = seconds();
 
  // Cálculo de la integral y el error.
  double pi = std::acos(-1.0);
  double volumen = (pi*pi) / 2.0;
   
  double integral = (16.0/N) * sumatoria;
  double error = std::fabs(integral - volumen) / volumen;

  valorIntegral = integral;
  valorError = error;
  
  std::cout << "Número de hilos: " << num_procesos << std::endl;
  std::cout << "Tiempo en completar el proceso: " << t_final - t_inicial <<  std::endl;
  std::cout << "Integral: "<< integral << std::endl;
  std::cout << "Error obtenido: " << error << std::endl;
}


// Método que devuelve el valor de la integral.
double MC::getIntVal() const{
  return valorIntegral;
}


// Método que devuelve el valor de iteraciones 'N'.
double MC::getNVal() const{
  return N;
}

// Método que devuelve el valor del error cometido.
double MC::getErrVal() const{
  return valorError;
}
