CXX=g++
CXXVERSION=c++11
CXXFLAGS=-Wall -Wextra -pedantic-errors -g3 -std=${CXXVERSION}

all 	: graph.o main.o
	$(CXX) graph.o main.o -o main $(CXXFLAGS)

%.o	: %.c
	$(CXX) -c $@ $(CXXFLAGS)

