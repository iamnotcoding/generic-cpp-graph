#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>

#include "graph.hpp"

bool Graph::IsAdjacent(std::string from, std::string to)
{
	if (std::find(edges.begin(), edges.end(), Edge(from, to)) == edges.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

const std::vector<std::string> &Graph::Neighbors(std::string v)
{
	std::vector<std::string> *result;

	for (auto i : adjList)
	{
		if (i.first.first == v)
		{
			result = &(i.second);
		}
	}

	return *result;
}

void Graph::AddVertex(std::string v)
{
	for (auto i : adjList)
	{
		if (i.first.first == v)
		{
			throw "vertex already exists";
		}
		else
		{
			break;
		}
	}

	adjList.push_back(
		std::make_pair(std::make_pair(v, nullptr), std::vector<std::string>()));
}

void Graph::RemoveVertex(std::string v)
{
	decltype(adjList.begin()) i;

	for (i = adjList.begin(); i != adjList.end(); i++)
	{
		if (i->first.first == v)
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

void *Graph::GetVertexValue(std::string v)
{
	void *result = nullptr;

	for (auto i : adjList)
	{
		if (i.first.first == v)
		{
			result = i.first.second;
		}
	}

	return result;
}

void Graph::AddEdge(std::string from, std::string to, double w)
{
	if (IsAdjacent(from, to))
	{
		throw "the edge already exists";
	}

	edges.push_back(Edge(from, to, w));
}

void Graph::RemoveEdge(std::string from, std::string to)
{
	edges.erase(std::remove(edges.begin(), edges.end(), Edge(from, to)),
				edges.end());
}

double Graph::GetEdgeWeight(std::string v1, std::string v2)
{
	return edges[(edges.end() -
				  std::find(edges.begin(), edges.end(), Edge(v1, v2)))]
		.w;
}

void Graph::SetEdgeWeight(std::string v1, std::string v2, double w)
{
	edges[(edges.end() - std::find(edges.begin(), edges.end(), Edge(v1, v2)))]
		.w = w;
}

#endif
