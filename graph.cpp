#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

#include "graph.hpp"

void Graph::AddVertex(int v)
{
	for (auto i : adjList)
	{
		if (i.first == v)
		{
			throw "vertex already exists";
		}
		else
		{
			break;
		}
	}

	adjList.push_back(std::make_pair(v, std::vector<int>()));
}

void Graph::RemoveVertex(int v)
{
	decltype(adjList.begin()) i;

	for (i = adjList.begin(); i != adjList.end(); i++)
	{
		if (i->first == v)
		{
			adjList.erase(i);

			break;
		}
	}

	if (i == adjList.end())
	{
		throw "v is not present";
	}
}

void Graph::AddEdge(int v1, int v2, double w = 1)
{
	bool isEdgePresent = false;

	for (auto i : edges)
	{
		if (i == Edge(v1, v2))
		{
            isEdgePresent = true;

            throw "the edge already exists";
		}
	}

    if (!isEdgePresent)
    {
        edges.push_back(Edge(v1,v2,w));
    }
}
#endif