// #include <iostream>
// #include <chrono>
// #include <vector>
// #include <utility>
// #include <algorithm>
#include "algoritmos.h"

bool myfunction (std::pair<int, int> i, std::pair<int, int> j) 
{
	return (i.second/i.first) > (j.second/j.first);
}



int main()//int argc, char const *argv[])
{
	std::pair <int, int> x1 (1, 5);
	std::pair <int, int> x2 (2, 8);
	std::pair <int, int> x3 (25, 4);
	std::pair <int, int> x4 (16, 10);
	std::pair <int, int> x5 (2, 6);
	std::pair <int, int> x6 (1, 6);
	std::vector<std::pair<int, int>> acciones = {x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5};/*,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5,
	                                             x1, x2, x3, x4, x5, x1, x2, x3, x4, x5, x1, x2, x3, x4, x5};*/

	std::sort(acciones.begin(), acciones.end());
	// std::sort(acciones.begin(), acciones.end(), ordenarCrecientePorRetorno);
	std::cout << acciones << "\n";
	
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

	// std::pair <int, int> x1 (25,10);
	// std::pair <int, int> x2 (25,9);
	// std::pair <int, int> x3 (25,8);
	// std::pair <int, int> x4 (25,7);
	// std::pair <int, int> x5 (25,6);
	// std::pair <int, int> x6 (25,5);
	// std::vector<std::pair<int, int>> acciones3 = {x1, x2, x3, x4, x5, x6}; 
	// std::sort(acciones3.begin(), acciones3.end(), myfunction);
	// std::cout << acciones << "\n";

	


	// printf("%d\n", solucionFB(acciones, 25));

	// std::sort(acciones.begin(), acciones.end(), myfunction);
	// std::cout << acciones << "\n";
	// printf("%d\n", solucionBT(acciones, 25));

	// std::sort(acciones2.begin(), acciones2.end(), myfunction);
	// printf("%d\n", solucionFB(acciones3, 25));

	// printf("%d\n", solucionBT(acciones2, 769));

	// printf("%d\n", solucionBT(acciones3, 25));

	return 0;
}
