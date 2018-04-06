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

TEST(TestFuerzaBruta, HaySolucion)
{
	pair<int,int> x5(6, 8);
	pair<int,int> x3(5, 10);
	pair<int,int> x4(7, 7);
	pair<int,int> x2(4, 1);
	pair<int,int> x1(3, 9);
	vector<pair<int,int>> v = {x5, x3, x4, x2, x1};

	EXPECT_EQ(solucionFuerzaBruta(v, 7), 10);
	EXPECT_EQ(solucionFuerzaBruta(v, 18), 28);
	EXPECT_EQ(solucionFuerzaBruta(v, 25), 35);

	pair<int,int> x6(18,28);
	v.push_back(x6);
	EXPECT_EQ(solucionFuerzaBruta(v, 18), 28);
	v.pop_back();

	pair<int,int> x7(25, 35);
	v.push_back(x7);
	EXPECT_EQ(solucionFuerzaBruta(v, 25), 35);
	v.pop_back();
}