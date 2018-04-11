#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "../src/algoritmos.h"

#define TAM_FUERZA_BRUTA 1000
// #define TAM_BACKTRACKING 10
#define NUMERO_MUESTRAS 30

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


/*
   EXPERIMENTO FB1
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 100
   * Retornos al azar entre 1 y 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoFB1(int min_size, int max_size, int granularity)
{
	/* 
	   Acá voy a guardar el tiempo promedio que tarda el algoritmo
	   para cada tamaño de vector.
	   Indices:
	   	- 0 y 4: fuerza bruta
	   	- 1 y 5: backtracking
	   	- 2 y 6: backtracking con pesos en orden decreciente
	   	- 3 y 7: programación dinámica
	   Capacidades máximas:
	    - 0, 1, 2 y 3: 2*(suma de todos los costos)
	    - 4, 5, 6 y 7: suma de la mitad de todos los costos
	*/

	vector<double> resultados[8];

	// Código "tomado prestado" de StackOverflow
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 100); // define the range

	for (int i = min_size; i < max_size+1; i+=granularity)
	{
		printf("Tamaño: %d\n", i);
		// La convención de índices es la misma que para resultados
		vector<double> resultados_parciales[8];

		// Para cada longitud del vector, tomo 30 muestras
		for (int j = 0; j < NUMERO_MUESTRAS; ++j)
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
			// else
			// {
			// 	resultados_parciales[0].push_back(0.0);
			// }

			// Después veo si tengo que cambiar este número
			// if (i <= TAM_BACKTRACKING)
			// {
			// 	auto startBacktracking = chrono::steady_clock::now();
			// 	solucionBacktracking(v, 2*sum_w);
			// 	auto endBacktracking = chrono::steady_clock::now();
			// 	auto diffBacktracking = endBacktracking - startBacktracking;
			// 	resultados_parciales[1].push_back(chrono::duration <double, milli> (diffBacktracking).count());
			// }
			// else
			// {
			// 	resultados_parciales[1].push_back(0.0);
			// }

			// if (i <= TAM_BACKTRACKING)
			// {
			// 	vector<pair<int,int>> v_back_copado(v);
			// 	reverse(v_back_copado.begin(), v_back_copado.end());
			// 	auto startBacktrackingCopado = chrono::steady_clock::now();
			// 	solucionBacktracking(v_back_copado, 2*sum_w);
			// 	auto endBacktrackingCopado = chrono::steady_clock::now();
			// 	auto diffBacktrackingCopado = endBacktrackingCopado - startBacktrackingCopado;
			// 	resultados_parciales[2].push_back(chrono::duration <double, milli> (diffBacktrackingCopado).count());
			// }
			// else
			// {
			// 	resultados_parciales[2].push_back(0.0);
			// }


			// auto startProgDinamica = chrono::steady_clock::now();
			// solucionProgDinamica(v, 2*sum_w);
			// auto endProgDinamica = chrono::steady_clock::now();
			// auto diffProgDinamica = endProgDinamica - startProgDinamica;
			// resultados_parciales[3].push_back(chrono::duration <double, milli> (diffProgDinamica).count());



			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);

			if (i <= TAM_FUERZA_BRUTA)
			{
				/* Corro el algoritmo de fuerza bruta solo para tamaños chicos.
				   Si no, tarda demasiado */
				auto startFuerzaBruta2 = chrono::steady_clock::now();
				solucionFuerzaBruta(v, 2*sum_mitad_w);
				auto endFuerzaBruta2 = chrono::steady_clock::now();
				auto diffFuerzaBruta2 = endFuerzaBruta2 - startFuerzaBruta2;
				resultados_parciales[4].push_back(chrono::duration <double, milli> (diffFuerzaBruta2).count());
			}
			// else
			// {
			// 	resultados_parciales[4].push_back(0.0);
			// }

			// Después veo si tengo que cambiar este número
			// if (i <= TAM_BACKTRACKING)
			// {
			// 	auto startBacktracking2 = chrono::steady_clock::now();
			// 	solucionBacktracking(v, 2*sum_mitad_w);
			// 	auto endBacktracking2 = chrono::steady_clock::now();
			// 	auto diffBacktracking2 = endBacktracking2 - startBacktracking2;
			// 	resultados_parciales[5].push_back(chrono::duration <double, milli> (diffBacktracking2).count());
			// }
			// else
			// {
			// 	resultados_parciales[5].push_back(0.0);
			// }

			// if (i <= TAM_BACKTRACKING)
			// {
			// 	vector<pair<int,int>> v_back_copado(v);
			// 	reverse(v_back_copado.begin(), v_back_copado.end());
			// 	auto startBacktrackingCopado2 = chrono::steady_clock::now();
			// 	solucionBacktracking(v_back_copado, 2*sum_mitad_w);
			// 	auto endBacktrackingCopado2 = chrono::steady_clock::now();
			// 	auto diffBacktrackingCopado2 = endBacktrackingCopado2 - startBacktrackingCopado2;
			// 	resultados_parciales[6].push_back(chrono::duration <double, milli> (diffBacktrackingCopado2).count());
			// }
			// else
			// {
			// 	resultados_parciales[6].push_back(0.0);
			// }


		// 	auto startProgDinamica2 = chrono::steady_clock::now();
		// 	solucionProgDinamica(v, 2*sum_mitad_w);
		// 	auto endProgDinamica2 = chrono::steady_clock::now();
		// 	auto diffProgDinamica2 = endProgDinamica2 - startProgDinamica2;
		// 	resultados_parciales[7].push_back(chrono::duration <double, milli> (diffProgDinamica2).count());
		}

		// Calculo los promedios de tiempos y me los guardo
		if (resultados_parciales[0].size()== 0) resultados_parciales[0].push_back(0);
		if (resultados_parciales[1].size()== 0) resultados_parciales[1].push_back(0);
		if (resultados_parciales[2].size()== 0) resultados_parciales[2].push_back(0);
		if (resultados_parciales[3].size()== 0) resultados_parciales[3].push_back(0);
		if (resultados_parciales[4].size()== 0) resultados_parciales[4].push_back(0);
		if (resultados_parciales[5].size()== 0) resultados_parciales[5].push_back(0);
		if (resultados_parciales[6].size()== 0) resultados_parciales[6].push_back(0);
		if (resultados_parciales[7].size()== 0) resultados_parciales[7].push_back(0);

		double proms[8];
		for (int i = 0; i < 8; ++i)
		{
			proms[i] = resultados_parciales[i][0];
		}

		//fb
		for (unsigned int i = 1; i < resultados_parciales[0].size(); ++i)
		{
			proms[0] += resultados_parciales[0][i];
			proms[4] += resultados_parciales[4][i];
		}

		//bcktrck
		for (unsigned int i = 1; i < resultados_parciales[1].size(); ++i)
		{
			proms[1] += resultados_parciales[1][i];
			proms[5] += resultados_parciales[5][i];

			proms[2] += resultados_parciales[2][i];
			proms[6] += resultados_parciales[6][i];
		}

		//pd
		for (unsigned int i = 1; i < resultados_parciales[2].size(); ++i)
		{
			proms[3] += resultados_parciales[3][i];
			proms[7] += resultados_parciales[7][i];
		}

		for (int i = 0; i < 8; ++i)
		{
			resultados[i].push_back(proms[i]/resultados_parciales[i].size());
		}
	}
	
	// Guardo los resultados en un archivo de texto
	ofstream outfile;
	outfile.open("exp_fb_1.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 1; i < resultados[3].size(); ++i)
	{
		outfile << asd << ","
			    << ((i <= TAM_FUERZA_BRUTA) ? resultados[0][i] : 0) << ","
			    // << ((i <= TAM_BACKTRACKING) ? resultados[1][i] : 0) << ","
			    // << ((i <= TAM_BACKTRACKING) ? resultados[2][i] : 0) << ","
			    // << resultados[3][i] << ","
			    << ((i <= TAM_FUERZA_BRUTA) ? resultados[4][i] : 0) //<< ","
			    // << ((i <= TAM_BACKTRACKING) ? resultados[5][i] : 0) << ","
			    // << ((i <= TAM_BACKTRACKING) ? resultados[6][i] : 0) << ","
			    // << resultados[7][i] << endl;
			    << endl;
		asd += granularity;
	}

	outfile.close();

}

/* 
   EXPERIMENTO FB2
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 1000
   * Retornos al azar entre 1 y 1000
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoFB2(int min_size, int max_size, int granularity)
{
	/* 
	   Acá voy a guardar el tiempo promedio que tarda el algoritmo
	   para cada tamaño de vector.
	   Capacidades máximas:
	    - 0: 2*(suma de todos los costos)
	    - 1: suma de la mitad de todos los costos
	*/

	vector<double> resultados[2];

	// Código "tomado prestado" de StackOverflow
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 1000); // define the range

	for (int i = min_size; i < max_size+1; i+=granularity)
	{
		printf("Tamaño: %d\n", i);
		// La convención de índices es la misma que para resultados
		vector<double> resultados_parciales[2];

		// Para cada longitud del vector, tomo 30 muestras
		for (int j = 0; j < NUMERO_MUESTRAS; ++j)
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

			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionFuerzaBruta(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionFuerzaBruta(v, 2*sum_mitad_w);
			auto endFuerzaBruta2 = chrono::steady_clock::now();
			auto diffFuerzaBruta2 = endFuerzaBruta2 - startFuerzaBruta2;
			resultados_parciales[1].push_back(chrono::duration <double, milli> (diffFuerzaBruta2).count());
		}

		// Calculo los promedios de tiempos y me los guardo
		double proms[2];
		proms[0] = resultados_parciales[0][0];
		proms[1] = resultados_parciales[1][0];

		for (unsigned int i = 1; i < resultados_parciales[0].size(); ++i)
		{
			proms[0] += resultados_parciales[0][i];
			proms[1] += resultados_parciales[1][i];
		}

		for (int i = 0; i < 2; ++i)
		{
			resultados[i].push_back(proms[i]/resultados_parciales[i].size());
		}
	}

	// Guardo los resultados en un archivo de texto
	ofstream outfile;
	outfile.open("exp_fb_2.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 1; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}



int main()
{
	printf("%s\n", "Empiezo...");
	experimentoFB2(1, 20, 1);
	printf("%s\n", "Terminé! :)");

	return 0;
}
