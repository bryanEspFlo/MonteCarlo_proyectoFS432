

# File MCsharem.cpp

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**MCsharem.cpp**](MCsharem_8cpp.md)

[Go to the documentation of this file](MCsharem_8cpp.md)


```C++
#include <iostream>
#include <cmath>
#include "MCsharem.hpp"
#include <random>
#include <omp.h>
#include <sys/time.h>

MC::MC(int num_N){
  N = num_N;
  valorIntegral = 0.0;
  valorError = 0.0;
  time_Procs = 0.0;
} 

int MC::Esphere4D(double x1, double x2, double x3, double x4){
   int val_func = 0;
  
   if(sqrt(x1*x1 + x2*x2 + x3*x3 + x4*x4) <= 1){
     val_func = 1;
   }
  
  return val_func;
}

double MC::seconds(){
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0; 
  return sec;
}

void MC::calcInt(){

  int sumatoria = 0;
  int num_procesos;
 
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);
 
  double t_inicial = seconds();
  #pragma omp parallel
  {
 
   #pragma omp for reduction(+: sumatoria)
   for(int i = 0; i < N; i++){
      sumatoria += Esphere4D(distribution(generator), distribution(generator),
                             distribution(generator), distribution(generator));
    }
  }
  double t_final = seconds();
 
  double pi = std::acos(-1.0);
  double volumen = (pi*pi) / 2.0;
   
  double integral = (16.0/N) * sumatoria;
  double error = std::fabs(integral - volumen) / volumen;

  valorIntegral = integral;
  valorError = error;
  
  time_Procs = t_final - t_inicial;
}

double MC::getIntVal() const{
  return valorIntegral;
}

double MC::getNVal() const{
  return N;
}

double MC::getErrVal() const{
  return valorError;
}

double MC::getTime() const{
  return time_Procs;
}
```


