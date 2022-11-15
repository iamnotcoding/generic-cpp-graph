#include <iostream>
#include <unordered_set>

#include "graph.hpp"

using namespace std;

int count = 0;

template <typename VertexData_t = VoidVertexData>
class CatchCow : public Graph<VertexData_t>
{
  public:
	int InfectedVirusCount(string v)
	{
		//cout << "cur vertex : " << v << endl;

		visited.insert(v);

		for (int i = 0; i < (int)(*this)[v].size(); i++)
		{
			if (!IsVisited((*this)[v][i]))
			{
				InfectedVirusCount((*this)[v][i]);
			}
		}

		return (int)visited.size() - 1;
	}

  private:
	unordered_set<string> visited;

	bool IsVisited(const string &computer_name)
	{
		if (visited.find(computer_name) == visited.end())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};

int main()
{
	int n, m;
	Virus<> g;

	cin >> n;
	cin >> m;

	for (int i = 0; i < n; i++)
	{
		g += to_string(i + 1);
	}

	for (int i = 0; i < m; i++)
	{
		string c1, c2;

		cin >> c1 >> c2;

		g.AddEdge(c1, c2);
	}


	cout << g.InfectedVirusCount("1");
}