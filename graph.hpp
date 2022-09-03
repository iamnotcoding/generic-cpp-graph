#include <iostream>
#include <vector>

struct Edge
{
	int v1;
	int v2;
	double w;

	Edge(int v1, int v2, double w = 1) : v1(v1), v2(v2), w(w)
	{
	}

	bool operator==(const Edge &rhs)
	{
		bool result = false;

		if ((v1 == rhs.v1 && v2 == rhs.v2) || (v1 == rhs.v2 && v2 == rhs.v1))
		{
			result = true;
		}

		return result;
	}

    bool operator!=(const Edge &rhs)
    {
        bool result = !operator==(rhs);

        return result;
    }
};

class Graph
{
  public:
	bool Adjacent(int from, int to); // tests whether there is an edge from the
									 // vertex 'from to the vertex 'to';
	void Neighbors(int v); // lists all vertices 'v' such that there is an edge
						   // from the vertex 'v' to the vertex y;
	void AddVertex(int v); // adds the vertex 'v', if it is not there;
	void RemoveVertex(int v); // removes the vertex 'v', if it is there;
	void AddEdge(int from, int to,
				 double w); // adds the edge from the vertex 'from' to
							// the vertex 'to', if it is not there;
	void RemoveEdge(int from,
					int to); // removes the edge from the vertex 'from' to the
							 // vertex 'to', if it is there;
	float GetEdgeValue(
		int v1,
		int v2); // returns the value associated with the edge (from, to);
	void SetEdgeValue(
		int v1, int v2,
		double w); // sets the value associated with the edge (from, tp) to w.
  private:
	// std::pair<vertex number, connected vertexes>
	bool IsEdgeSame(Edge x, Edge y);

	std::vector<std::pair<int, std::vector<int>>> adjList;
	std::vector<Edge> edges;
};