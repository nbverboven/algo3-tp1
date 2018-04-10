#include "algoritmos.h"

/**************************************************************
 *                       Fuerza Bruta                         *
 **************************************************************/

void solucionFuerzaBrutaAux(const std::vector<std::pair<int, int>> &acciones, 
	                        const int &capital_de_inversion, int &max_retorno, 
	                        int &costo_parcial, int &retorno_parcial, unsigned int i)
{
	if (i == acciones.size())
	{
		/* Si estoy en el problema de tamaño 0 (raíz), veo si encontré una solución
		   y si es preciso actualizar el máximo */
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
	}
	else
	{
		/* Si no, pruebo agregando el k-ésimo elemento (rama afirmativa) y luego
		   pruebo no agregarlo (rama negativa). Notar que, luego de retornar de 
		   la primera llamada recursiva, se modifica la solución parcial para
		   reflejar la decisión que se toma */
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

		solucionFuerzaBrutaAux(acciones, capital_de_inversion, max_retorno, 
			                   costo_parcial, retorno_parcial, i+1);

		costo_parcial -= acciones[i].first;
		retorno_parcial -= acciones[i].second;

		solucionFuerzaBrutaAux(acciones, capital_de_inversion, max_retorno, 
			                   costo_parcial, retorno_parcial, i+1);
	}
}


int solucionFuerzaBruta(const std::vector<std::pair<int, int>> &acciones, 
	                    const int &capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionFuerzaBrutaAux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

	return resultado_final;
}



/**************************************************************
 *                      Backtracking                          *
 *               (podando por factibilidad)                   *
 **************************************************************/

void solucionBacktrackingAux(const std::vector<std::pair<int, int>> &acciones, 
	                         const int &capital_de_inversion, int &max_retorno, 
	                         int &costo_parcial, int &retorno_parcial, unsigned int i)
{
	if (i == acciones.size())
	{
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
	}
	else
	{
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

		/* El único punto en el que este algoritmo difiere del de fuerza bruta.
		   Sólo se prueba agregar un elemento si esto no da lugar a una solución
		   inválida */
		if (costo_parcial <= capital_de_inversion)
		{
			solucionBacktrackingAux(acciones, capital_de_inversion, max_retorno, 
				                    costo_parcial, retorno_parcial, i+1);
		}

		retorno_parcial -= acciones[i].second;
		costo_parcial -= acciones[i].first;

		solucionBacktrackingAux(acciones, capital_de_inversion, max_retorno, 
			                    costo_parcial, retorno_parcial, i+1);
	}
}


int solucionBacktracking(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionBacktrackingAux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

	return resultado_final;
}



/**************************************************************
 *                  Programación dinámica                     *
 **************************************************************/

int solucionProgDinamica(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion)
{
	/* Creo la matriz de soluciones e inicializo en 0 las 
	   soluciones para el problema de tamaño 0 */
	std::vector<std::vector<int>> soluciones(acciones.size()+1,std::vector<int>(capital_de_inversion+1));

	for (int j = 0; j <= capital_de_inversion; ++j)
	{
		soluciones[0][j] = 0;
	}

	/* Resuelvo el subproblema de tamaño i
	   para cada capacidad máxima j */
	for (unsigned int i = 1; i <= acciones.size(); ++i)
	{
		for (int j = 0; j <= capital_de_inversion; ++j)
		{
			if (acciones[i-1].first > j)
			{
				/* Este es el caso en que un elemento no puede ser agregado a la 
				   solución por superar la capacidad máxima */
				soluciones[i][j] = soluciones[i-1][j];
			}
			else
			{
				/* En este caso, para obtener la solución óptima, tomo los valores
				   agregando el elemento en cuestión y dejándolo de lado y me quedo
				   con el máximo */
				std::pair<int,int> actual = acciones[i-1];
				int costo_actual = actual.first;
				int retorno_actual = actual.second;

				int solucion_si_agrego_actual = soluciones[i-1][j-costo_actual] + retorno_actual;
				int solucion_si_no_agrego_actual = soluciones[i-1][j];

				int mejor_solucion = std::max(solucion_si_agrego_actual,
					                          solucion_si_no_agrego_actual);

				soluciones[i][j] = mejor_solucion;

			}
		}
	}

	/* Retorno la solución al problema de tamaño longitud(acciones) */
	return soluciones[acciones.size()][capital_de_inversion];
}