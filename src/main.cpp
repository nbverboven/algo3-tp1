#include <iostream>
#include <vector>
#include <utility>
#include "algoritmos.h"

int main()
{
	int cant_elem;
	int capac_max;
	std::vector<std::pair<int,int>> v;

	/* Leo desde el standard input la cantidad de
	   elementos que tendrá el vector y la capacidad
	   máxima de la mochila */
	std::cin >> cant_elem;
	std::cin >> capac_max;

	/* Leo los elementos y los agrego de a uno al vector */
	while (cant_elem > 0)
	{
		std::pair<int,int> e;
		std::cin >> e.first;
		std::cin >> e.second;
		v.push_back(e);
		--cant_elem;
	}

	/* Descomentar el algoritmo que se prefiera
	   y comentar el resto */
	// std::cout << solucionFuerzaBruta(v, e);
	// std::cout << solucionBacktracking(v, e);
	std::cout << solucionProgDinamica(v, capac_max) << std::endl;

	return 0;
}