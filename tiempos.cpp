#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "algoritmos.h"

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


/* EXPERIMENTO FUERZA BRUTA 1
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 100
   * Retornos al azar entre 1 y 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoFuerzaBruta1(int max_size, int granularity)
{
	// Acá voy a guardar el tiempo promedio que tarda el algoritmo
	// para cada tamaño de vector
	vector<double> resultados;
	vector<double> resultados2;

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 100); // define the range


	for (int i = 1; i < max_size+1; i+=granularity)
	{

		vector<double> resultados_parciales;
		vector<double> resultados_parciales2;

		// Para cada longitud del vector, tomo 30 muestras
		for (int j = 0; j < 30; ++j)
		{
			// Genero el vector de tamaño i de pares al azar
			vector<pair<int,int>> v;
			for (int k = 0; k < i; ++k)
			{
				pair<int,int> x(distr(eng), distr(eng));
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			// Corro el algoritmo de fuerza bruta y veo cuánto tarda
			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionFuerzaBruta(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales.push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);

			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionFuerzaBruta(v, sum_mitad_w);
			auto endFuerzaBruta2 = chrono::steady_clock::now();
			auto diffFuerzaBruta2 = endFuerzaBruta2 - startFuerzaBruta2;
			resultados_parciales2.push_back(chrono::duration <double, milli> (diffFuerzaBruta2).count());
		}

		// Calculo el promedio de tiempos y me lo guardo
		double prom = resultados_parciales[0];
		double prom2 = resultados_parciales2[0];
		for (unsigned int i = 1; i < resultados_parciales.size(); ++i)
		{
			prom += resultados_parciales[i];
			prom2 += resultados_parciales2[i];
		}

		resultados.push_back(prom/resultados_parciales.size());
		resultados2.push_back(prom/resultados_parciales2.size());
	}
	
	// Guardo los resultados en un archivo de tessto
	ofstream outfile;
	outfile.open("exp_fb_1.csv", ios::out);

	// Escribo todos los resultados en el archivo
	outfile << "0,0.0,0.0"  << endl;
	int asd = 0;
	for (unsigned int i = 0; i < resultados.size(); ++i)
	{
		outfile << asd+granularity << "," << resultados[i] 
		                           << "," << resultados2[i] 
		                           << endl;
		asd += granularity;
	}

	outfile.close();

}


int main()
{
	// cout << endl << endl;
	// auto startBacktracking = chrono::steady_clock::now();
	// solucionBacktracking1(v, 25);
	// auto endBacktracking = chrono::steady_clock::now();
	// auto diffBacktracking = endBacktracking - startBacktracking;
	// cout << "Tiempo utilizado por Backtracking " << chrono::duration <double, milli> (diffBacktracking).count() << " ms" << endl;

	experimentoFuerzaBruta1(30, 5);

	return 0;
}
