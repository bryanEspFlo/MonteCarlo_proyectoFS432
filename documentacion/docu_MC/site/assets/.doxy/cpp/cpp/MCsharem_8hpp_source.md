

# File MCsharem.hpp

[**File List**](files.md) **>** [**include**](dir_d44c64559bbebec7f509842c48db8b23.md) **>** [**MCsharem.hpp**](MCsharem_8hpp.md)

[Go to the documentation of this file](MCsharem_8hpp.md)


```C++
#ifndef MC_HPP
#define MC_HPP

class MC{
  private:
    MC();

    int Esphere4D(double x1, double x2, double x3, double x4);

    double valorIntegral; 
    double valorError; 
    double time_Procs; 
   
    double seconds();

  public:
    int N; 

    MC(int N);

    void calcInt();

    double getIntVal() const;

    double getNVal() const;

    double getTime() const;

    double getErrVal() const; // Muestra el valor del error cometido.
};
#endif // MC_HPP
```


