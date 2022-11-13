#include <iostream>

#include "graph.hpp"

class Student
{
  public:
	std::string name;
	int height;

	Student(std::string name, int height) : name(name), height(height)
	{
	}
	Student &operator=(const Student &rhs)
	{
		name = rhs.name, height = rhs.height;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, Student s);
};

std::ostream& operator<<(std::ostream& os, Student s)
{
    os << "hi my name is " << s.name << " and my height is " << s.height;
    return os;
}

int main()
{
	Student jack("Jack", 160);
	Graph<Student> g;

	g.AddVertex("A");
	g.AddVertex("B");
	g.AddVertex("C");
	// g.AddVertex("B");
	g.AddEdge("A", "B");
	g.AddEdge("C", "B");
	g.SetVertexData("A", jack);
	std::cout << g.GetVertexData("A") << std::endl;

	g.SetEdgeWeight("A", "B", 0.3);
	g.SetEdgeWeight("C", "B", 0.4);
	std::cout << g.GetEdgeWeight("C", "B") << std::endl;
}