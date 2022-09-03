#include <iostream>

#include "graph.hpp"

int main()
{
    Graph g;

    g.AddVertex("A");
    g.AddEdge("A", "B");
    g.RemoveEdge("A", "B");

    for (auto v : g.Neighbors("A"))
    {
        std::cout << v;
    }
}