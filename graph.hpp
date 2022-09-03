#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "edge.hpp"

class Graph
{
  public:
	// returns whether there is an edge from the vertex 'from' to the vertex 'to'
	bool IsAdjacent(std::string from, std::string to);
	// lists all vertices 'v' such that there is an edge from the vertex 'v' to
	// the vertex y;
	const std::vector<std::string> &Neighbors(std::string v);
	// adds the vertex 'v', if it is not there;
	void AddVertex(std::string v);
	// removes the vertex 'v', if it is there;
	void RemoveVertex(std::string v);
	// returns the value associated with the vertex x;
	void *GetVertexValue(std::string v);
	// sets the value associated with the vertex x to v.
	void SetVertexValue(std::string v, void *val);
	// adds the edge from the vertex 'from' to the vertex 'to', if it is not
	// there;
	void AddEdge(std::string from, std::string to, double w = 1);
	// removes the edge from the vertex 'from' to the vertex 'to', if it is
	// there;
	void RemoveEdge(std::string from, std::string to);
	// returns the weigh associated with the edge (v1, v2) or vice versa
	double GetEdgeWeight(std::string v1, std::string v2);
	// sets the weigh associated with the edge (v1, v2) or vice versa.
	void SetEdgeWeight(std::string v1, std::string v2, double w);

  private:
	std::vector<std::pair<std::pair<std::string, void *>, std::vector<std::string>>> GetVertex(std::string v);

	std::vector<Edge> edges;

	// std::pair<std::pair<vertex, vertex data(nullptr if none)>, adjacent
	// vertexes>
	std::vector<std::pair<std::pair<std::string, void *>, std::vector<std::string>>> adjList;
};