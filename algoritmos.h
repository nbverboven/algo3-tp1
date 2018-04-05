#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

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


bool tieneSentidoAgregar(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion, int costo_parcial, int &max_retorno,
	                     int retorno_parcial, unsigned int k)
{
	while (k < acciones.size() && costo_parcial+acciones[k].first <= capital_de_inversion)
	{
		// if (costo_parcial+acciones[k].first <= capital_de_inversion)
		// {
			costo_parcial += acciones[k].first;
			retorno_parcial += acciones[k].second;
		// }

		++k;
	}

	return retorno_parcial > max_retorno;
}


void solucionBacktracking2Aux(const std::vector<std::pair<int, int>> &acciones, 
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

		if (tieneSentidoAgregar(acciones, capital_de_inversion, costo_parcial, 
			                    max_retorno, retorno_parcial, i+1))
		{
			solucionBacktracking2Aux(acciones, capital_de_inversion, max_retorno, 
				                    costo_parcial, retorno_parcial, i+1);
		}

		retorno_parcial -= acciones[i].second;
		costo_parcial -= acciones[i].first;

		if (tieneSentidoAgregar(acciones, capital_de_inversion, costo_parcial,
			                    max_retorno,retorno_parcial, i+1))
		{
			solucionBacktracking2Aux(acciones, capital_de_inversion, max_retorno, 
				                    costo_parcial, retorno_parcial, i+1);
		}
	}
}


int solucionBacktracking2(const std::vector<std::pair<int, int>> &acciones, 
	                      const int &capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionBacktracking2Aux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

	return resultado_final;
}


/**************************************************************
 *                  Programación dinámica                     *
 **************************************************************/
int solucionProgDinamica(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion)
{
	int res = 0;
	int costo = 0;
	int retorno = 0;
	std::vector<std::pair<int, int>> solucion_parcial;
	std::vector<std::pair<int, int>> no_usados;

	for (int i = 0; i < capital_de_inversion; ++i)
	{
		// Resuelvo el subproblema de tamaño i

		int costo_parcial = 0;
		int retorno_parcial = 0;

		for (unsigned int j = 0; j < acciones.size(); ++j)
		{
			
		}

		costo += costo_parcial;
		retorno += retorno_parcial;
	}

	return res;
}


#endif // ALGORITMOS_H