#include "algoritmos.h"
#include "gtest/gtest.h"

using namespace std;


TEST(TestFuerzaBruta, VectorVacio)
{
	vector<pair<int,int>> v = {};

	EXPECT_EQ(solucionFuerzaBruta(v, 25), 0);
}

TEST(TestFuerzaBruta, NoHaySolucion)
{
	pair<int,int> x1(3, 3);
	pair<int,int> x2(4, 4);
	pair<int,int> x3(5, 5);
	vector<pair<int,int>> v = {x1, x2, x3};

	EXPECT_EQ(solucionFuerzaBruta(v, 2), 0);
	
}