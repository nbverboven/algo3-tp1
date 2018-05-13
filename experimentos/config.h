#ifndef CONFIG_H
#define CONFIG_H 

#define NUMERO_MUESTRAS 25

using namespace std;

// Funciones auxiliares para los experimentos
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

#endif
