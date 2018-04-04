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

void solucionFBAux(const std::vector<std::pair<int, int>> &acciones, 
	               const int &capital_de_inversion, int &max_retorno, 
	               int &costo_parcial, int &retorno_parcial, unsigned int i)
{
	if (i == acciones.size())
	{
		printf("(costo: %d, retorno: %d)\n", costo_parcial, retorno_parcial);
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
	}
	else
	{
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

		solucionFBAux(acciones, capital_de_inversion, max_retorno, 
			                   costo_parcial, retorno_parcial, i+1);

		costo_parcial -= acciones[i].first;
		retorno_parcial -= acciones[i].second;

		solucionFBAux(acciones, capital_de_inversion, max_retorno, 
			                   costo_parcial, retorno_parcial, i+1);
	}
}


int solucionFB(const std::vector<std::pair<int, int>> &acciones, 
	           const int &capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionFBAux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

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


bool myfunction (std::pair<int, int> i, std::pair<int, int> j) 
{
	return (i.second/i.first) > (j.second/j.first);
}



int main()//int argc, char const *argv[])
{
	// std::pair <int, int> x1 (1, 5);
	// std::pair <int, int> x2 (2, 8);
	// std::pair <int, int> x3 (25, 4);
	// std::pair <int, int> x4 (16, 10);
	// std::pair <int, int> x5 (2, 6);
	// std::pair <int, int> x6 (1, 6);
	// std::vector<std::pair<int, int>> acciones = {x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5};/*,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5};*/
	
	// std::vector<std::pair<int, int>> acciones2 = {x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	//                                              x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5};

	std::pair <int, int> x1 (25,10);
	std::pair <int, int> x2 (25,9);
	std::pair <int, int> x3 (25,8);
	std::pair <int, int> x4 (25,7);
	std::pair <int, int> x5 (25,6);
	std::pair <int, int> x6 (25,5);
	std::vector<std::pair<int, int>> acciones3 = {x1, x2, x3, x4, x5, x6}; 
	std::sort(acciones3.begin(), acciones3.end(), myfunction);
	// std::cout << acciones << "\n";

	// std::cout << acciones << "\n";


	// printf("%d\n", solucionFB(acciones, 25));

	// std::sort(acciones.begin(), acciones.end(), myfunction);
	// std::cout << acciones << "\n";
	// printf("%d\n", solucionBT(acciones, 25));

	// std::sort(acciones2.begin(), acciones2.end(), myfunction);
	// printf("%d\n", solucionFB(acciones3, 25));

	// printf("%d\n", solucionBT(acciones2, 769));

	printf("%d\n", solucionBT(acciones3, 25));

	return 0;
}
