#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
// #include <vector>
// #include <utility>
// #include <algorithm>
#include "algoritmos.h"

using namespace std;

bool myfunction (std::pair<int, int> i, std::pair<int, int> j) 
{
	return (i.second/i.first) > (j.second/j.first);
}

int sumaDeCostos(const vector<pair<int,int>> &v)
{
	int max_w = 0;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		max_w += v[i].first;
	}

	return max_w;
}

int main()//int argc, char const *argv[])
{
	// cout << "steady_clock" << endl;
 //    cout << chrono::steady_clock::period::num << endl;
 //    cout << chrono::steady_clock::period::den << endl;
 //    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

	// cout << endl << endl;
	// auto startBacktracking = chrono::steady_clock::now();
	// solucionBacktracking1(v, 25);
	// auto endBacktracking = chrono::steady_clock::now();
	// auto diffBacktracking = endBacktracking - startBacktracking;
	// cout << "Tiempo utilizado por Backtracking " << chrono::duration <double, milli> (diffBacktracking).count() << " ms" << endl;



	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 100); // define the range

	
	// Testeo primero con un vector de 10 elementos para 
	// ver cuántas muestras son necesarias

	// En este caso, el vector resultados va a terminar teniendo
	// 300 elementos
	vector<chrono::duration <double, milli>> resultados;

	for (int i = 0; i < 300; ++i)
	{
		vector<chrono::duration <double, milli>> resultados_parciales;

		// Esto lo voy a hacer para muestras de tamaño 1, 2, etc. hasta 
		// llegar a 300
		for (int j = 0; j <= i; ++j)
		{
			// Genero el vector de tamaño 10 de pares al azar
			vector<pair<int,int>> v;
			for (int k = 0; k < 10; ++k)
			{
				pair<int,int> x(distr(eng), distr(eng));
				v.push_back(x);
			}

			int max_w = sumaDeCostos(v);

			// Corro el algoritmo de fuerza bruta y veo cuánto tarda
			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionFuerzaBruta(v, 2*max_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales.push_back((chrono::duration <double, milli>) (diffFuerzaBruta).count());
		}

		// Calculo el promedio de tiempos y me lo guardo
		chrono::duration <double, milli> asd = resultados_parciales[0];
		for (unsigned int i = 1; i < resultados_parciales.size(); ++i)
		{
			asd += resultados_parciales[i];
		}

		resultados.push_back(asd/resultados_parciales.size());
	}

	// Guardo los resultados en un archivo de testo
	ofstream outfile;
	outfile.open("resultados_prueba.csv", ios::app);

	// Escribo todos los resultados en el archivo
	for (unsigned int i = 0; i < resultados.size(); ++i)
	{
		outfile << i+1 << "," << resultados[i].count() << endl;
	}

	outfile.close();

	return 0;
}
