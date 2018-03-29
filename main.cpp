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


int solucionFuerzaBruta(const std::vector<std::pair<int, int>> &acciones, int capital_de_inversion)
{
	int total_elecciones_posibles = (1 << acciones.size()) - 1; // pow(2, acciones.size()) - 1;
	int resultado_final = 0;

	for (int i = total_elecciones_posibles; i > 0; --i)
	{
		int rep_binaria = i;
		int retorno_iteracion = 0;
		int costo_iteracion = 0;

		for (unsigned int j = 0; j < acciones.size(); ++j)
		{
			costo_iteracion += acciones[acciones.size()-j-1].first * (rep_binaria & 1);
			retorno_iteracion += acciones[acciones.size()-j-1].second * (rep_binaria & 1);
			rep_binaria = rep_binaria >> 1;
		}

		if (costo_iteracion <= capital_de_inversion && retorno_iteracion > resultado_final)
		{
			resultado_final = retorno_iteracion;
		}

		printf("iteración %d: (costo: %d, retorno: %d)\n", i, costo_iteracion, retorno_iteracion);
	}

	return resultado_final;
}



int main()//int argc, char const *argv[])
{
	std::pair <int, int> x1 (1, 5);
	std::pair <int, int> x2 (2, 8);
	std::pair <int, int> x3 (25, 4);
	std::pair <int, int> x4 (16, 10);
	std::pair <int, int> x5 (2, 6);
	std::vector<std::pair<int, int>> acciones = {x1, x2, x3, x4, x5};
	std::vector<std::pair<int, int>> acciones2 = {};
	// std::cout << acciones << "\n";

	printf("%d\n", solucionFuerzaBruta(acciones, 25));
	printf("%d\n", solucionFuerzaBruta(acciones2, 25));
	return 0;
}