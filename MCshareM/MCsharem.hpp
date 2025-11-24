#ifndef MC_HPP
#define MC_HPP

class MC{
  private:
    MC(); // Constructor por defecto.
    int Esphere4D(double x1, double x2, double x3, double x4); // Método que devuelve los valores de la función a integrar.
    double valorIntegral;
    double valorError;
    double seconds(); // Método para obtener el tiempo entre iteraciones.
  public:
    int N; // Cantidad de iteraciones.
    MC(int N); //  Constructor personnalizado.
    void calcInt(); // Método que calcula la integral con MC.
    double getIntVal() const; // Muestra el valor de la integral.
    double getNVal() const; // Muestra el valor 'N' de iteraciones.
    double getErrVal() const; // Muestra el valor del error cometido.
};
#endif
