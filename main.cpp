#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <cmath>

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


void solucionFuerzaBrutaAux(const std::vector<std::pair<int, int>> &acciones, const int &capital_de_inversion, 
	                        int &max_retorno, int &costo_parcial, int &retorno_parcial, unsigned int i)
{
	if (i >= acciones.size())
	{
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
		return;
	}
	else
	{
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

		solucionFuerzaBrutaAux(acciones, capital_de_inversion, max_retorno, costo_parcial, retorno_parcial, i+1);

		costo_parcial -= acciones[i].first;
		retorno_parcial -= acciones[i].second;

		solucionFuerzaBrutaAux(acciones, capital_de_inversion, max_retorno, costo_parcial, retorno_parcial, i+1);

		return;
	}
}


int solucionFuerzaBruta(const std::vector<std::pair<int, int>> &acciones, int capital_de_inversion)
{
	int resultado_final = 0;
	int costo = 0;
	int retorno = 0;

	solucionFuerzaBrutaAux(acciones, capital_de_inversion, resultado_final, costo, retorno, 0);

	return resultado_final;
}



bool puedoSeguirAgregando(const std::vector<std::pair<int, int>> &acciones, const int &capital_de_inversion, int &costo_parcial, 
	                       unsigned int k)
{
	bool res = false;

	for (unsigned int i = k; i < acciones.size(); ++i)
	{
		if (costo_parcial+acciones[i].first<=capital_de_inversion)
		{
			res = true;
		}
	}

	return res;
}

void solucionBacktrackingAux(const std::vector<std::pair<int, int>> &acciones, const int &capital_de_inversion, 
	                        int &max_retorno, int &costo_parcial, int &retorno_parcial, unsigned int i)
{
	if (!puedoSeguirAgregando(acciones, capital_de_inversion, costo_parcial, i))
	{
		printf("(costo: %d, retorno: %d)\n", costo_parcial, retorno_parcial);
		if (costo_parcial <= capital_de_inversion && retorno_parcial > max_retorno)
		{
			max_retorno = retorno_parcial;
		}
		return;
	}
	else
	{
		costo_parcial += acciones[i].first;
		retorno_parcial += acciones[i].second;

		solucionBacktrackingAux(acciones, capital_de_inversion, max_retorno, 
			                    costo_parcial, retorno_parcial, i+1);

		costo_parcial -= acciones[i].first;
		retorno_parcial -= acciones[i].second;
		
		solucionBacktrackingAux(acciones, capital_de_inversion, max_retorno, 
			                    costo_parcial, retorno_parcial, i+1);

		return;
	}
}

int solucionBacktracking(const std::vector<std::pair<int, int>> &acciones, const int &capital_de_inversion)
{
	int res = 0;
	int asd1 = 0;
	int asd2 = 0;
	// bool asd3 = false;
	solucionBacktrackingAux(acciones, capital_de_inversion, res, asd1, asd2, 0);//, asd3);

	return res;
}



int main()//int argc, char const *argv[])
{
	std::pair <int, int> x1 (1, 5);
	std::pair <int, int> x2 (2, 8);
	std::pair <int, int> x3 (25, 4);
	std::pair <int, int> x4 (16, 10);
	std::pair <int, int> x5 (2, 6);
	std::pair <int, int> x6 (1, 6);
	std::vector<std::pair<int, int>> acciones = {x1, x2, x3, x4, x5};
	std::vector<std::pair<int, int>> acciones3 = {x1, x2, x4};
	// std::cout << acciones << "\n";

	// printf("%d\n", solucionFuerzaBruta(acciones, 25));
	// printf("%d\n", solucionBacktracking(acciones3, 5));
	printf("%d\n", solucionBacktracking(acciones, 25));
	return 0;
}
