#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>

void solucionFuerzaBrutaAux(const std::vector<std::pair<int, int>> &acciones, 
	                        const int &capital_de_inversion, int &max_retorno, 
	                        int &costo_parcial, int &retorno_parcial, unsigned int i);

int solucionFuerzaBruta(const std::vector<std::pair<int, int>> &acciones, 
	                    const int &capital_de_inversion);

void solucionBacktrackingAux(const std::vector<std::pair<int, int>> &acciones, 
	                         const int &capital_de_inversion, int &max_retorno, 
	                         int &costo_parcial, int &retorno_parcial, unsigned int i);

int solucionBacktracking(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion);

int solucionProgDinamica(const std::vector<std::pair<int, int>> &acciones, 
	                     const int &capital_de_inversion);


#endif // ALGORITMOS_H