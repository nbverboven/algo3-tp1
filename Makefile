CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -O3 -std=c++11

.PHONY: all clean

all: clean main

clean:
	rm -f *.o
	rm -f main

main: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@