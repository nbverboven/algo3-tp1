.PHONY: all clean

CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -O3 -std=c++11

all: exp1 exp2 exp3 exp4

clean:
	rm -f *.o
	rm -f *.csv
	rm -f exp1 exp2 exp3 exp4


exp1: exp1.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

exp2: exp2.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

exp3: exp3.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

exp4: exp4.cpp algoritmos.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $<

