CXX=g++
CXXVERSION=c++11
CXXFLAGS=-Wall -Wextra -pedantic-errors -g3 -std=${CXXVERSION}

all	: main.cpp
	${CXX} main.cpp ${CXXFLAGS}

clean	:
	rm *.o main