# generic graph library in c++
## This graph implementation is based on the that of the wikipedia :<a href=https://en.wikipedia.org/wiki/Graph_(abstract_data_type)#Operations> link </a>

### This libaray is header-only

#### How to create a graph
*If VertexDataType is a class, it requires a copy constructor*
   
    Graph<VertexDataType> g;
*If you want to add vertexes initally*
    
    Graph<VertexDataType> g{"A", "B", "C"};
*If you need not to use vertex data*

    Graph<> g;

#### How to add a vertex
    g.AddVertex("vertex name");

or

    g += "vertex name";

#### How to delete a vertex
    g.RemoveVertex("vertex name")

or

    g -= "vertex name"
#### How to set a vertex data
    g.SetVertexData("vertex name", data);

#### How to get a vertex data
    g.GetVertexData("vertex name");

#### How to check wether a vertex exists
    g.IsVertexExist("vertex name");
#### How to add an edge
*edges are directed "from", "to" != "to", "from"*
*(the weight defaults to 0)*

    g.AddEdge("from", "to");

#### How to delete an edge
    g.RemoveEdge("from", "to");
#### How to set an edge weight (weight = double)
    g.SetEdgeWeight("from", "to", weight);
#### How to get an edge weight
    g.GetEdgeWeight("from", "to");

#### How to check wether an edge exists  
    IsAdjacent("from", "to");
#### How to get neighbors (return type = vector\<std::string>)
    g.Neighbors("v");

or

    g["v"];
#### How to Get all the vertexes
    g.GetAllVertexes();

#### How to get the numbers of neighbors
*Don't worry, this operation is O(1)*

    g.Neighbors("v").size();
    
or

    g.["v"].size();

#### How to copy a graph
    g1 = g2
#### How to clear a graph 
    g.Clear()
