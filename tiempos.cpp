#include <iostream>
#include <chrono>
// #include <vector>
// #include <utility>
// #include <algorithm>
#include "algoritmos.h"

using namespace std;

bool myfunction (std::pair<int, int> i, std::pair<int, int> j) 
{
	return (i.second/i.first) > (j.second/j.first);
}

int main()//int argc, char const *argv[])
{
	cout << "steady_clock" << endl;
    cout << chrono::steady_clock::period::num << endl;
    cout << chrono::steady_clock::period::den << endl;
    cout << "steady = " << boolalpha << chrono::steady_clock::is_steady << endl << endl;

	return 0;
}
