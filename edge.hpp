#ifndef EDGE_HPP
#define EDGE_HPP

struct Edge
{
	std::string from;
	std::string to;
	double w;

	Edge(std::string from, std::string to, double w = 1) : from(from), to(to), w(w)
	{
	}

	bool operator==(const Edge &rhs)
	{
		bool result = false;

		if (from == rhs.from && to == rhs.to)
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

#endif