#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "../src/algoritmos.h"
#include "config.h"

using namespace std;

/* 
   EXPERIMENTO PD1
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 100
   * Retornos al azar entre 1 y 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD1(int min_size, int max_size, int granularity)
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
	std::uniform_int_distribution<> distr(1, 100); // define the range

	for (int i = min_size; i < max_size+1; i+=granularity)
	{
		//printf("Tamaño: %d\n", i);
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
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_1.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}


/* 
   EXPERIMENTO PD2
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 1000
   * Retornos al azar entre 1 y 1000
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD2(int min_size, int max_size, int granularity)
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
		//printf("Tamaño: %d\n", i);
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
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_2.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}


/* 
   EXPERIMENTO PD3
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 100
   * Retornos = costo + 10
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD3(int min_size, int max_size, int granularity)
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
	std::uniform_int_distribution<> distr(1, 100); // define the range

	for (int i = min_size; i < max_size+1; i+=granularity)
	{
		//printf("Tamaño: %d\n", i);
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
				int elem = distr(eng);
				pair<int,int> x(elem, elem+10);
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_3.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}


/* 
   EXPERIMENTO PD4
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Costos al azar entre 1 y 1000
   * Retornos = costo + 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD4(int min_size, int max_size, int granularity)
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
		//printf("Tamaño: %d\n", i);
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
				int elem = distr(eng);
				pair<int,int> x(elem, elem+100);
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_4.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}


/* 
   EXPERIMENTO PD5
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Retornos al azar entre 1 y 100
   * Costo = Retorno + 10
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD5(int min_size, int max_size, int granularity)
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
		//printf("Tamaño: %d\n", i);
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
				int elem = distr(eng);
				pair<int,int> x(elem+10, elem);
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_5.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
	{
		outfile << asd << ","
			    << resultados[0][i] << ","
			    << resultados[1][i] << endl;
		asd += granularity;
	}

	outfile.close();
}


/* 
   EXPERIMENTO PD6
   * # muestras: 30
   * Tamaño del vector: a determinar
   * Retornos al azar entre 1 y 1000
   * Costo = Retorno + 100
   * Capacidad máxima: 2*(suma de todos los costos) y
                       suma de la mitad de todos los costos
*/
void experimentoPD6(int min_size, int max_size, int granularity)
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
		//printf("Tamaño: %d\n", i);
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
				int elem = distr(eng);
				pair<int,int> x(elem+100, elem);
				v.push_back(x);
			}

			// Para calcular la capacidad máxima
			int sum_w = sumaDeCostos(v);

			auto startFuerzaBruta = chrono::steady_clock::now();
			solucionProgDinamica(v, 2*sum_w);
			auto endFuerzaBruta = chrono::steady_clock::now();
			auto diffFuerzaBruta = endFuerzaBruta - startFuerzaBruta;
			resultados_parciales[0].push_back(chrono::duration <double, milli> (diffFuerzaBruta).count());

			// Realizo el experimento con el otro costo máximo
			int sum_mitad_w = sumaDeMediosCostos(v);
			
			auto startFuerzaBruta2 = chrono::steady_clock::now();
			solucionProgDinamica(v, sum_w/5);
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
	outfile.open("exp_pd_6.csv", ios::out);

	// Escribo todos los resultados en el archivo
	int asd = min_size;
	for (unsigned int i = 0; i < resultados[0].size(); ++i)
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
	printf("%s\n", "Empiezando PD1...");
	experimentoPD1(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	printf("%s\n", "Empiezando PD2...");
	experimentoPD2(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	printf("%s\n", "Empiezando PD3...");
	experimentoPD3(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	printf("%s\n", "Empiezando PD4...");
	experimentoPD4(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	printf("%s\n", "Empiezando PD5...");
	experimentoPD5(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	printf("%s\n", "Empiezando PD6 ..");
	experimentoPD6(1, 28, 1);
	printf("%s\n", "Terminé! :)");

	return 0;
}
