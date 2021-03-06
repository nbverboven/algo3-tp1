.PHONY: all clean

CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -O3 -std=c++11
SRC_DIR = src

all: main

clean:
	rm -f *.o
	rm -f main

main: $(SRC_DIR)/main.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<
