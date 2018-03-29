#include <iostream>
#include <chrono>
#include <vector>
#include <utility>


int solucionFuerzaBruta(const std::vector<std::pair<int, int>> &acciones, int capital_de_inversion)
{
	int total_elecciones_posibles = ( 2^acciones.size() ) - 1;
	int resultado_final = 0;

	for ( int i = total_elecciones_posibles; i > 0; --i )
	{
		int rep_binaria = i;
		int resultado_iteracion = 0;

		for ( unsigned int j = 0; j < acciones.size(); ++j )
		{
			resultado_iteracion += acciones[acciones.size()-j].first * (rep_binaria & 1);
			rep_binaria = rep_binaria >> 1;
		}

		if ( resultado_iteracion <= capital_de_inversion && resultado_iteracion > resultado_final )
		{
			resultado_final = resultado_iteracion;
		}
	}

	return resultado_final;
}



int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}