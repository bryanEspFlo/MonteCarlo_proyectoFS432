#ifndef MC_HPP
#define MC_HPP

/**
 * @brief Clase MC (Monte Carlo) que calcula integrales con el método homónimo.
 * 
 * La clase MC permite calcular el volumen de una hiperesfera unitaria en 4 dimenciones.
 */
class MC{
  private:
    /**
     * @brief Constructor por defecto de la clase MC.
     *
     * El constructor por defecto se deja por fuera para que no se pueda crear un objeto
     * de tipo MC sin indicar un número de interaciones.
     */
    MC();

    /**
     * @brief Método que indica si el punto está dentro de la hiperesfera.
     * @param x1 Coordenada del punto en el eje x1.
     * @param x2 Coordenada del punto en el eje x2.
     * @param x3 Coordenada del punto en el eje x3.
     * @param x4 Coordenada del punto en el eje x4.
     * @return Devuelve 1 si el punto está dentro de la hiperesfera y 0 si no.
     */
    int Esphere4D(double x1, double x2, double x3, double x4);

    double valorIntegral; ///< Valor del volumen de la hiperesfera calculado con Monte Carlo.
    double valorError; ///< Valor del error cometido en base al valor teórico real del volumen.
    double time_Procs; ///< Tiempo en realizar el cálculo de la integral con Monte Carlo.
   
    /**
     * @brief Método para saber el tiempo que toma una iteración.
     * @return El tiempo en segundos que ha transcurrido desde que se invoca.
     */
    double seconds();

  public:
    int N; ///< Cantidad de iteraciones para realizar Monte Carlo.

    /**
     * @brief Constructor personalizado de la clase MC.
     * @param N Atributo con la cantidad de interaciones.
     */
    MC(int N);

    /**
     * @brief Método que calcula el volumen de la hiperesfera con Monte carlo.
     */
    void calcInt();

    /**
     * @brief Devuelve el valor de la integral calculada con Monte Carlo.
     */
    double getIntVal() const;

    /**
     * @brief Devuelve la cantidad de iteraciones realizadas.
     */
    double getNVal() const;

    /**
     * @brief Devuelve el tiempo que se toma en calcular la integral con Monte Carlo.
     */
    double getTime() const;

    /**
     * @brief Devuelve el error cometido al calcular la integral.
     */
    double getErrVal() const; // Muestra el valor del error cometido.
};
#endif // MC_HPP
