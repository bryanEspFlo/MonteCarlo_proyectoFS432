#include <cmath>
#include <iostream>
#include <random>
#include <omp.h>
#include <sys/time.h>

//
double seconds(){
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
 
  return sec;
}


// Función del integrando para el cálculo del volumen.
int funcIntegrando(double x1, double x2, double x3, double x4){
  int func = 0;

  if(sqrt(x1*x1 + x2*x2 + x3*x3 + x4*x4) <= 1){
    func = 1;
  }

  return func;
}


// Función que calcula la integral utilizando Monte Carlo.
double MonteCarlo(int (*func) (double x1, double x2, double x3, double x4), int N){
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
      sumatoria += func(distribution(generator), distribution(generator), 
                        distribution(generator), distribution(generator));
    }
  }
  double t_final = seconds();

  // Cálculo de la integral y el error.
  double pi = std::acos(-1.0);
  double Volumen = (pi*pi) / 2.0;

  double Integral = (16.0/N) * sumatoria;
  double error = std::fabs(Integral - Volumen) / Volumen;

  std::cout << "Número de hilos: " << num_procesos << std::endl;
  std::cout << "Tiempo en completar el proceso: " << t_final - t_inicial <<  std::endl;
  std::cout << "Error cometido: " << error <<  std::endl;
  std::cout << "" << std::endl;

  return Integral;
}


// Función principal.
int main(){

  int N = 10000000;

  double Inte = MonteCarlo(funcIntegrando, N);

  std::cout << "Valor calculado de la integral: " << Inte << std::endl;

  return 0;
}
