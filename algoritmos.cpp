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
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
	}
	else
	{
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
		// printf("(costo: %d, retorno: %d)\n", costo_parcial, retorno_parcial);
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
	}
	else
	{
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

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
	std::vector<std::vector<int>> soluciones(acciones.size()+1,std::vector<int>(capital_de_inversion+1));

	for (int j = 0; j <= capital_de_inversion; ++j)
	{
		soluciones[0][j] = 0;
	}


	// Resuelvo el subproblema de tamaño i
	// para cada n
	for (unsigned int i = 1; i <= acciones.size(); ++i)
	{
		for (int j = 0; j <= capital_de_inversion; ++j)
		{
			if (acciones[i-1].first > j)
			{
				soluciones[i][j] = soluciones[i-1][j];
			}
			else
			{
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

	return soluciones[acciones.size()][capital_de_inversion];
}