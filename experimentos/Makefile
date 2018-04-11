.PHONY: all clean

CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -O3 -std=c++11
SRC_DIR = ../src

EXPNUM = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18

all: exp1

clean:
	rm -f *.o
	rm -f *.csv
	rm -f exp1


exp1: exp1.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<

