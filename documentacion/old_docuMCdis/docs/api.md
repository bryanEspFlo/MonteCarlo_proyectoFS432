# API — Clase MonteCarloMPI

La clase `MonteCarloMPI` se encarga de:

- Dividir el número total de puntos entre procesos MPI
- Generar puntos aleatorios
- Evaluar si están dentro de la hiperesfera
- Combinar resultados con MPI_Reduce
- Retornar el volumen estimado
