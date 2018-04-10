#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<int, int>> &v)
{
	os << "[";

	for (unsigned int i = 0; i < v.size(); ++i)
	{
		os << "(" << v[i].first << "," << v[i].second << ")";

		if (i < v.size()-1)
		{
			os << ", ";
		}
	}

	os << "]";
	return os;
}


void imprimirVector(const std::vector<std::vector<int>> &v)
{
	cout << "[" << endl;

	for (unsigned int i = 0; i < v.size(); ++i)
	{
		cout << "[";

		for (unsigned int j = 0; j < v[i].size(); ++j)
		{
			cout << v[i][j] ;

			if (j < v[i].size()-1)
			{
				cout << ", ";
			}
		}

		cout << "]" << endl;
	}

	cout << "]" << endl;
}


/**************************************************************
 *                       Fuerza Bruta                         *
 **************************************************************/

void solucionFuerzaBrutaAux(const std::vector<std::pair<int, int>> &acciones, 
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


void solucionBacktracking1Aux(const std::vector<std::pair<int, int>> &acciones, 
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
			solucionBacktracking1Aux(acciones, capital_de_inversion, max_retorno, 
				                    costo_parcial, retorno_parcial, i+1);
		}

		retorno_parcial -= acciones[i].second;
		costo_parcial -= acciones[i].first;

		solucionBacktracking1Aux(acciones, capital_de_inversion, max_retorno, 
			                    costo_parcial, retorno_parcial, i+1);
	}
}


int solucionBacktracking1(const std::vector<std::pair<int, int>> &acciones, 
	                      const int &capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionBacktracking1Aux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

	return resultado_final;
}


/**************************************************************
 *                      Backtracking                          *
 *               (podando por optimalidad)                    *
 **************************************************************/


// bool tieneSentidoAgregar(const std::vector<std::pair<int, int>> &acciones, 
// 	                     const int &capital_de_inversion, int costo_parcial, int &max_retorno,
// 	                     int retorno_parcial, unsigned int k)
// {
// 	while (k < acciones.size() && costo_parcial+acciones[k].first <= capital_de_inversion)
// 	{
// 		// if (costo_parcial+acciones[k].first <= capital_de_inversion)
// 		// {
// 			costo_parcial += acciones[k].first;
// 			retorno_parcial += acciones[k].second;
// 		// }

// 		++k;
// 	}

// 	return retorno_parcial > max_retorno;
// }


// void solucionBacktracking2Aux(const std::vector<std::pair<int, int>> &acciones, 
// 	                          const int &capital_de_inversion, int &max_retorno, 
// 	                          int &costo_parcial, int &retorno_parcial, unsigned int i)
// {
// 	if (i == acciones.size())
// 	{
// 		// printf("(costo: %d, retorno: %d)\n", costo_parcial, retorno_parcial);
// 		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
// 		{
// 			max_retorno = retorno_parcial;
// 		}
// 	}
// 	else
// 	{
// 		costo_parcial += acciones[i].first;
// 		retorno_parcial += acciones[i].second;

// 		if (tieneSentidoAgregar(acciones, capital_de_inversion, costo_parcial, 
// 			                    max_retorno, retorno_parcial, i+1))
// 		{
// 			solucionBacktracking2Aux(acciones, capital_de_inversion, max_retorno, 
// 				                    costo_parcial, retorno_parcial, i+1);
// 		}

// 		retorno_parcial -= acciones[i].second;
// 		costo_parcial -= acciones[i].first;

// 		if (tieneSentidoAgregar(acciones, capital_de_inversion, costo_parcial,
// 			                    max_retorno,retorno_parcial, i+1))
// 		{
// 			solucionBacktracking2Aux(acciones, capital_de_inversion, max_retorno, 
// 				                    costo_parcial, retorno_parcial, i+1);
// 		}
// 	}
// }


// int solucionBacktracking2(const std::vector<std::pair<int, int>> &acciones, 
// 	                      const int &capital_de_inversion)
// {
// 	int resultado_final = 0;
// 	int costo = 0;
// 	int retorno = 0;

// 	solucionBacktracking2Aux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

// 	return resultado_final;
// }


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


#endif // ALGORITMOS_H