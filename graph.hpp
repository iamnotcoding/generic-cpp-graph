#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename VertexData_t> struct Vertex
{
	Vertex(std::string name) : name(name)
	{
	}

	~Vertex()
	{
		if (data != nullptr)
		{
			delete data;
		}
	}

	std::string name;
	VertexData_t *data = nullptr;
	std::vector<std::string> neighbors;
	std::vector<double> weights;
};

// Graph<vertex data type(defaults to int)>
template <typename VertexData_t = int> class Graph
{
  public:
	// returns whether there is an edge from the vertex 'from' to the vertex
	// 'to'
	bool IsAdjacent(std::string from, std::string to);
	// lists all vertices 'v' such that there is an edge from the vertex 'v' to
	// the vertex y;
	const std::vector<std::string> &Neighbors(std::string v);
	// adds the vertex 'v', if it is not there;
	void AddVertex(std::string v);
	// removes the vertex 'v', if it is there;
	void RemoveVertex(std::string v);
	// returns the value associated with the vertex x;
	const VertexData_t &GetVertexData(std::string v);
	// sets the value associated with the vertex x to v.
	void SetVertexData(std::string v, VertexData_t data);
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
	// std::vector<std::pair<std::pair<vertex name, vertex data>,
	// std::vector<std::pair<neighbor, weight>>>>
	std::vector<Vertex<VertexData_t>> vertexes;
};

template <typename VertexData_t>
bool Graph<VertexData_t>::IsAdjacent(std::string from, std::string to)
{
	bool isAjacent = true;
	typename std::vector<Vertex<VertexData_t>>::iterator fromVertex;
	typename std::vector<std::string>::iterator toVertex;

	// decltype(vertexes.begin()) fromVertex;
	// decltype(Vertex<VertexData_t>("placeholder").neighbors.begin()) toVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == from)
		{
			isFromVertexExists = true;
			fromVertex = vertex;
		}

		if (vertex->name == to)
		{
			isToVertexExists = true;
		}
	}

	if (!isFromVertexExists && !isToVertexExists)
	{
		throw std::runtime_error("vertex " + from + "and " + to +
								 " doesn't exist");
	}
	else if (!isFromVertexExists)
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}
	else if (!isToVertexExists)
	{
		throw std::runtime_error("vertex " + to + " doesn't exist");
	}

	toVertex = std::find(fromVertex->neighbors.begin(),
						 fromVertex->neighbors.end(), to);

	if (toVertex == fromVertex->neighbors.end())
	{
		isAjacent = false;
	}

	return isAjacent;
}

template <typename VertexData_t>
const std::vector<std::string> &Graph<VertexData_t>::Neighbors(std::string v)
{
	int vertexIndex;

	for (vertexIndex = 0; vertexIndex < (int)vertexes.size(); vertexIndex++)
	{
		if (vertexes[vertexIndex].name == v)
		{
			break;
		}
	}

	return vertexes[vertexIndex].neighbors;
}

template <typename VertexData_t>
void Graph<VertexData_t>::AddVertex(std::string v)
{
	for (auto vertex : vertexes)
	{
		if (vertex.name == v)
		{
			throw std::runtime_error("vertex " + v + " already exists");
		}
	}

	vertexes.push_back(Vertex<VertexData_t>(v));
}

template <typename VertexData_t>
void Graph<VertexData_t>::RemoveVertex(std::string v)
{
	bool isVertexExist = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (*vertex.name == v)
		{
			vertexes.erase(vertex);
			isVertexExist = true;
		}
	}

	if (!isVertexExist)
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}
}

template <typename VertexData_t>
const VertexData_t &Graph<VertexData_t>::GetVertexData(std::string v)
{
	typename std::vector<Vertex<VertexData_t>>::iterator destVertex;
	bool isVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == v)
		{
			isVertexExists = true;
			destVertex = vertex;
		}
	}

	if (!isVertexExists)
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}

	return *(destVertex->data);
}

// The data will be copied. Requires assignment operator.
template <typename VertexData_t>
void Graph<VertexData_t>::SetVertexData(std::string v, VertexData_t data)
{
	typename std::vector<Vertex<VertexData_t>>::iterator destVertex;
	bool isVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == v)
		{
			isVertexExists = true;
			destVertex = vertex;
		}
	}

	if (!isVertexExists)
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}

	destVertex->data = new VertexData_t(data);
}

template <typename VertexData_t>
void Graph<VertexData_t>::AddEdge(std::string from, std::string to, double w)
{
	typename std::vector<Vertex<VertexData_t>>::iterator fromVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == from)
		{
			isFromVertexExists = true;
			fromVertex = vertex;
		}

		if (vertex->name == to)
		{
			isToVertexExists = true;
		}
	}

	if (!isFromVertexExists && !isToVertexExists)
	{
		throw std::runtime_error("vertex " + from + "and " + to +
								 " doesn't exist");
	}
	else if (!isFromVertexExists)
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}
	else if (!isToVertexExists)
	{
		throw std::runtime_error("vertex " + to + " doesn't exist");
	}

	fromVertex->neighbors.push_back(to);
	fromVertex->weights.push_back(0);
}

template <typename VertexData_t>
void Graph<VertexData_t>::RemoveEdge(std::string from, std::string to)
{
	typename std::vector<Vertex<VertexData_t>>::iterator fromVertex;
	typename std::vector<std::string>::iterator toVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == from)
		{
			isFromVertexExists = true;
			fromVertex = vertex;
		}

		if (vertex->name == to)
		{
			isToVertexExists = true;
		}
	}

	if (!isFromVertexExists && !isToVertexExists)
	{
		throw std::runtime_error("vertex " + from + "and " + to +
								 " doesn't exist");
	}
	else if (!isFromVertexExists)
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}
	else if (!isToVertexExists)
	{
		throw std::runtime_error("vertex " + to + " doesn't exist");
	}

	toVertex = std::find(fromVertex->neighbors.begin(),
						 fromVertex->neighbors.end(), to);

	if (toVertex == fromVertex->neighbors.end())
	{
		throw std::runtime_error("edge from " + from + " to " + to +
								 " doesn't exist");
	}

	fromVertex->neighbors.erase(toVertex);
}

template <typename VertexData_t>
double Graph<VertexData_t>::GetEdgeWeight(std::string from, std::string to)
{
	typename std::vector<Vertex<VertexData_t>>::iterator fromVertex;
	typename std::vector<std::string>::iterator toVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == from)
		{
			isFromVertexExists = true;
			fromVertex = vertex;
		}
	}

	if (!isFromVertexExists)
	{
		throw std::runtime_error("edge from " + from + " to " + to +
								 " doesn't exist");
	}

	for (auto vertex = fromVertex->neighbors.begin();
		 vertex != fromVertex->neighbors.end(); vertex++)
	{
		if (*vertex == to)
		{
			isToVertexExists = true;
			toVertex = vertex;
		}
	}

	if (!isToVertexExists)
	{
		throw std::runtime_error("edge from " + from + " to " + to +
								 " doesn't exist");
	}

	return fromVertex->weights[fromVertex->neighbors.begin() - toVertex];
}

template <typename VertexData_t>
void Graph<VertexData_t>::SetEdgeWeight(std::string from, std::string to,
										double w)
{
	typename std::vector<Vertex<VertexData_t>>::iterator fromVertex;
	typename std::vector<std::string>::iterator toVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists = false;

	for (auto vertex = vertexes.begin(); vertex != vertexes.end(); vertex++)
	{
		if (vertex->name == from)
		{
			isFromVertexExists = true;
			fromVertex = vertex;
		}
	}

	if (!isFromVertexExists)
	{
		throw std::runtime_error("edge from " + from + " to " + to +
								 " doesn't exist");
	}

	for (auto vertex = fromVertex->neighbors.begin();
		 vertex != fromVertex->neighbors.end(); vertex++)
	{
		if (*vertex == to)
		{
			isToVertexExists = true;
			toVertex = vertex;
		}
	}

	if (!isToVertexExists)
	{
		throw std::runtime_error("edge from " + from + " to " + to +
								 " doesn't exist");
	}

	fromVertex->weights[fromVertex->neighbors.begin() - toVertex] = w;
}
