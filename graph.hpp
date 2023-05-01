#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

/* This class doesn't have a copy constructor so as to prevent itself from being
 * copied */
class VoidVertexData
{
	VoidVertexData(const VoidVertexData&) = delete;
};

template <typename VertexData_t> struct Vertex
{
	~Vertex()
	{
		if (data != nullptr)
		{
			delete data;
		}
	}

	VertexData_t* data = nullptr;
	std::vector<std::string> neighbors;
	std::unordered_map<std::string, double> weights;
};

// Graph<vertex data type(defaults to VoidVertexData)>
template <typename VertexData_t = VoidVertexData> class Graph
{
public:
	Graph() = default;

	// Gets list of vertexes
	Graph(std::initializer_list<std::string> l)
	{
		for (auto v : l)
		{
			AddVertex(v);
		}
	}

	/* Returns whether there is an edge from the vertex 'from' to the vertex
	 'to'. */
	bool IsAdjacent(const std::string& from, const std::string& to);
	/* Returns a std::vector of vertics adjacent to v. */
	const std::vector<std::string>& Neighbors(const std::string& v);
	// Adds the vertex 'v', if it is not there.
	void AddVertex(const std::string& v);
	// Removes the vertex 'v', if it is there.
	void RemoveVertex(const std::string& v);
	/* Returns the data associated with the vertex x.
	The data will be copied so VertexData_t requires a copy constructor. */
	VertexData_t GetVertexData(const std::string& v);
	/* Sets the data associated with the vertex x to v.
	 The data will be copied so VertexData_t requires a copy constructor. */
	void SetVertexData(const std::string& v, const VertexData_t& data);
	/* Adds the edge from the vertex 'from' to the vertex 'to', if it is not
	there. */
	void AddEdge(const std::string& from, const std::string& to);
	/* removes the edge from the vertex 'from' to the vertex 'to', if it is
	 there. */
	void RemoveEdge(const std::string& from, const std::string& to);
	// returns the weigh associated with the edge (from, to).
	double GetEdgeWeight(const std::string& from, const std::string& to);
	// sets the weigh associated with the edge (from, to).
	void SetEdgeWeight(const std::string& from, const std::string& to,
		double w);
	// Returns true if the vertex exists, otherwise returns false.
	bool IsVertexExist(const std::string& v);
	// Gets all the vertexes
	std::vector<std::string> GetAllVertexes();
	// Clears the graph.
	void Clear()
	{
		vertexes.clear();
	}

	// The same as graph.Neighbors(v).
	const std::vector<std::string>& operator[](const std::string& v)
	{
		return Neighbors(v);
	}

	// The same as lhs.AddVertex(rhs).
	Graph<VertexData_t>& operator+=(const std::string& rhs)
	{
		AddVertex(rhs);

		return *this;
	}

	// The same as lhs.RemoveVertex(rhs).
	Graph<VertexData_t>& operator-=(const std::string& rhs)
	{
		RemoveVertex(rhs);

		return *this;
	}
private:
	typename std::unordered_map<std::string, Vertex<VertexData_t>> vertexes;
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		GetVertex(const std::string& v);
};

template <typename VertexData_t>
typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator Graph<
	VertexData_t>::GetVertex(const std::string& v)
{
	return vertexes.find(v);
}

template <typename VertexData_t>
bool Graph<VertexData_t>::IsVertexExist(const std::string& v)
{
	if (GetVertex(v) != vertexes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename VertexData_t>
bool Graph<VertexData_t>::IsAdjacent(const std::string& from,
	const std::string& to)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		fromVertex = GetVertex(from);
	bool result = true;

	if (fromVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}

	if (std::find(fromVertex->second.neighbors.begin(),
		fromVertex->second.neighbors.end(),
		to) == fromVertex->second.neighbors.end())
	{
		result = false;
	}

	return result;
}

template <typename VertexData_t>
const std::vector<std::string>& Graph<VertexData_t>::Neighbors(
	const std::string& v)
{
	if (GetVertex(v) == vertexes.end())
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}

	return vertexes[v].neighbors;
}

template <typename VertexData_t>
void Graph<VertexData_t>::AddVertex(const std::string& v)
{
	if (IsVertexExist(v))
	{
		throw std::runtime_error("vertex " + v + " already exists");
	}

	vertexes[v] = Vertex<VertexData_t>();
}

template <typename VertexData_t>
void Graph<VertexData_t>::RemoveVertex(const std::string& v)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		destVertex = GetVertex(v);

	if (destVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}
	else
	{
		vertexes.erase(destVertex);
	}
}

template <typename VertexData_t>
VertexData_t Graph<VertexData_t>::GetVertexData(const std::string& v)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		destVertex = GetVertex(v);

	if (destVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}

	return *(destVertex->second.data);
}

template <typename VertexData_t>
void Graph<VertexData_t>::SetVertexData(const std::string& v,
	const VertexData_t& data)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		destVertex = GetVertex(v);

	if (destVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + v + " doesn't exist");
	}

	destVertex->second.data = new VertexData_t(data);
}

template <typename VertexData_t>
void Graph<VertexData_t>::AddEdge(const std::string& from,
	const std::string& to)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		fromVertex = GetVertex(from);

	if (fromVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}

	if (GetVertex(to) == vertexes.end())
	{
		throw std::runtime_error("vertex " + to + " doesn't exist");
	}

	if (IsAdjacent(from, to))
	{
		throw std::runtime_error("edge " + from + " to " + to +
			" already exists");
	}

	fromVertex->second.neighbors.push_back(to);
	fromVertex->second.weights[to] = 0;
}

template <typename VertexData_t>
void Graph<VertexData_t>::RemoveEdge(const std::string& from,
	const std::string& to)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		fromVertex = GetVertex(from);
	typename std::vector<std::string>::iterator toVertex;
	bool isFromVertexExists = false;
	bool isToVertexExists;

	if (fromVertex == vertexes.end())
	{
		throw std::runtime_error("vertex " + from + " doesn't exist");
	}

	if (GetVertex(to) == vertexes.end())
	{
		throw std::runtime_error("vertex " + to + " doesn't exist");
	}

	if (!IsAdjacent(from, to))
	{
		throw std::runtime_error("edge " + from + "and " + to +
			" doesn't exist");
	}

	fromVertex.neighbors.erase(std::find(fromVertex.neighbors.begin(),
		fromVertex.neighbors.end(), to));
}

template <typename VertexData_t>
double Graph<VertexData_t>::GetEdgeWeight(const std::string& from,
	const std::string& to)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		fromVertex = GetVertex(from);
	typename std::vector<std::string>::iterator toVertex;
	bool isToVertexExists = false;

	if (fromVertex == vertexes.end())
	{
		throw std::runtime_error("edge from " + from + " to " + to +
			" doesn't exist");
	}

	for (auto vertex = fromVertex->second.neighbors.begin();
		vertex != fromVertex->second.neighbors.end(); vertex++)
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

	return fromVertex->second
		.weights[to];
}

template <typename VertexData_t>
void Graph<VertexData_t>::SetEdgeWeight(const std::string& from,
	const std::string& to, double w)
{
	typename std::unordered_map<std::string, Vertex<VertexData_t>>::iterator
		fromVertex = GetVertex(from);
	typename std::vector<std::string>::iterator toVertex;
	bool isToVertexExists = false;

	if (fromVertex == vertexes.end())
	{
		throw std::runtime_error("edge from " + from + " to " + to +
			" doesn't exist");
	}

	for (auto vertex = fromVertex->second.neighbors.begin();
		vertex != fromVertex->second.neighbors.end(); vertex++)
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

	fromVertex->second
		.weights[to] = w;
}

template <typename VertexData_t>
std::vector<std::string> Graph<VertexData_t>::GetAllVertexes()
{
	std::vector<std::string> result;

	for (auto& e : vertexes)
	{
		result.push_back(e.first);
	}

	return result;
}

#endif
