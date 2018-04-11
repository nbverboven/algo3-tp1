#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "algoritmos.h"

#define TAM_FUERZA_BRUTA 80
#define TAM_BACKTRACKING 80

using namespace std;

int sumaDeCostos(const vector<pair<int,int>> &v)
{
	int max_w = 0;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		max_w += v[i].first;
	}

	return max_w;
}

int sumaDeMediosCostos(const vector<pair<int,int>> &v)
{
	int max_w = 0;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		max_w += (v[i].first)/2;
	}

	return max_w;
}


/* EXPERIMENTO  1
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 100
   * Retornos al azar entre 1 y 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimento1(int max_size, int granularity)
{
	/* 
	   Acá voy a guardar el tiempo promedio que tarda el algoritmo
	   para cada tamaño de vector.
	   Indices:
	   	- 0 y 3: fuerza bruta
	   	- 1 y 4: backtracking
	   	- 2 y 5: programación dinámica
	   Capacidades máximas:
	    - 0, 1 y 2: 2*(suma de todos los costos)
	    - 3, 4,y 5: suma de la mitad de todos los costos
	*/

	vector<double> resultados[6];

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 100); // define the range

	for (int i = 1; i < max_size+1; i+=granularity)
	{
		// La convención de índices es la misma que para resultados
		vector<double> resultados_parciales[6];

		// Para cada longitud del vector, tomo 30 muestras
		for (int j = 0; j < 30; ++j)
		{
			/* Genero el vector de tamaño i de pares al azar.
			   Todos los algoritmos los aplico siempre sobre el
			   mismo vector, para poder comparar los tiempos.*/
			vector<pair<int,int>> v;
			for (int k = 0; k < i; ++k)
			{
				pair<int,int> x(distr(eng), distr(eng));
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			if (i <= TAM_FUERZA_BRUTA)
			{
				/* Corro el algoritmo de fuerza bruta solo para tamaños chicos.
				   Si no, tarda demasiado */
				auto startFuerzaBruta = chrono::steady_clock::now();
				solucionFuerzaBruta(v, 2*sum_w);
				auto endFuerzaBruta = chrono::steady_clock::now();
				auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
				resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());
			}
			else
			{
				resultados_parciales[0].push_back(0.0);
			}

			// Después veo si tengo que cambiar este número
			if (i <= TAM_BACKTRACKING)
			{
				auto startBacktracking = chrono::steady_clock::now();
				solucionBacktracking(v, 2*sum_w);
				auto endBacktracking = chrono::steady_clock::now();
				auto diffBacktracking = endBacktracking - startBacktracking;
				resultados_parciales[1].push_back(chrono::duration <double, milli> (diffBacktracking).count());
			}
			else
			{
				resultados_parciales[1].push_back(0.0);
			}


			auto startProgDinamica = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_w);
			auto endProgDinamica = chrono::steady_clock::now();
			auto diffProgDinamica = endProgDinamica - startProgDinamica;
			resultados_parciales[2].push_back(chrono::duration <double, milli> (diffProgDinamica).count());



			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);

			if (i <= 20)
			{
				/* Corro el algoritmo de fuerza bruta solo para tamaños chicos.
				   Si no, tarda demasiado */
				auto startFuerzaBruta2 = chrono::steady_clock::now();
				solucionFuerzaBruta(v, 2*sum_mitad_w);
				auto endFuerzaBruta2 = chrono::steady_clock::now();
				auto diffFuerzaBruta2 = endFuerzaBruta2 - startFuerzaBruta2;
				resultados_parciales[3].push_back(chrono::duration <double, milli> (diffFuerzaBruta2).count());
			}
			else
			{
				resultados_parciales[3].push_back(0.0);
			}

			// Después veo si tengo que cambiar este número
			if (i <= 25)
			{
				auto startBacktracking2 = chrono::steady_clock::now();
				solucionBacktracking(v, 2*sum_mitad_w);
				auto endBacktracking2 = chrono::steady_clock::now();
				auto diffBacktracking2 = endBacktracking2 - startBacktracking2;
				resultados_parciales[4].push_back(chrono::duration <double, milli> (diffBacktracking2).count());
			}
			else
			{
				resultados_parciales[4].push_back(0.0);
			}


			auto startProgDinamica2 = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_mitad_w);
			auto endProgDinamica2 = chrono::steady_clock::now();
			auto diffProgDinamica2 = endProgDinamica2 - startProgDinamica2;
			resultados_parciales[5].push_back(chrono::duration <double, milli> (diffProgDinamica2).count());
		}

		// Calculo los promedios de tiempos y me los guardo
		double proms[6];
		for (int i = 0; i < 6; ++i)
		{
			proms[i] = resultados_parciales[i][0];
		}

		//fb
		for (unsigned int i = 1; i < resultados_parciales[0].size(); ++i)
		{
			proms[0] += resultados_parciales[0][i];
			proms[3] += resultados_parciales[3][i];
		}

		//bcktrck
		for (unsigned int i = 1; i < resultados_parciales[1].size(); ++i)
		{
			proms[1] += resultados_parciales[1][i];
			proms[4] += resultados_parciales[4][i];
		}

		//pd
		for (unsigned int i = 1; i < resultados_parciales[2].size(); ++i)
		{
			proms[2] += resultados_parciales[2][i];
			proms[5] += resultados_parciales[5][i];
		}

		for (int i = 0; i < 6; ++i)
		{
			resultados[i].push_back(proms[i]/resultados_parciales[i].size());
		}
	}
	
	// Guardo los resultados en un archivo de texto
	ofstream outfile;
	outfile.open("exp_1.csv", ios::out);

	// Escribo todos los resultados en el archivo
	outfile << "0,0.0,0.0,0.0,0.0,0.0,0.0"  << endl;
	int asd = 0;
	for (unsigned int i = 0; i < resultados[2].size(); ++i)
	{
		outfile << asd+granularity << ","
			    << ((i <= TAM_FUERZA_BRUTA) ? resultados[0][i] : 0.0) << ","
			    << ((i <= TAM_BACKTRACKING) ? resultados[1][i] : 0.0) << ","
			    << resultados[2][i] << ","
			    << ((i <= TAM_FUERZA_BRUTA) ? resultados[3][i] : 0.0) << ","
			    << ((i <= TAM_BACKTRACKING) ? resultados[4][i] : 0.0) << ","
			    << resultados[5][i] << endl;
		asd += granularity;
	}

	outfile.close();

}


int main()
{
	experimento1(50, 1);

	return 0;
}
