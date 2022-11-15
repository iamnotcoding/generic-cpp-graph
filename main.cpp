#include "graph.hpp"

int main()
{
	Graph<> g{"A"};
//	g -= "A";

	std::cout << g.IsVertexExist("A");
}