//HW4 maxflow and bipartite matching
//Due: 11:59pm, Thursday Oct. 27.
/*
When performing BFS for max flow or max matching, you need to explore neighbors in the order of increasing node IDs.
For example, if a node has unvisited neighbors 7, 3, 5, and 2.  Then the order for exploring neighbors will be 2, 3, 5, and 7.
This implies that you have to sort neighbors when forming the graph.

For simplicity, in the case of max flow problem, assume there will be at most one directed edge from a node to another node.
It is possible that given two nodes n1, and n2, there is a directed edge from n1 to n2 and there is also another directed edge from n2 to n1.

For max matching problem, since you are dealing with undirected graph, for simplicity, you can assume that there will at most one edge between
any two nodes.

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

//You will implement the following three functions.  No additional functions are allowed.
void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<...>>& T, int s, int t);//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<...>>& T, int s, int t);//Graph, Table, source, sink
int BFS(vector<list<pair<int, int>>>& G, vector<tuple<...>>& T, int s, int t);
//Both BipartiteMatching and MaxFlow will call BFS.
//Return the flow on the path found by BFS or 0 if no path found

int main() {
	
	vector<list<pair<int, int>>> Graph1;
	vector<tuple<...>> Table1;//  Design the tuple. Remember that you will perform BFS

	//Read in graph from graph1.txt
	//Data initialization

	MaxFlow(Graph1, Table1, source, sink);

	//Read in graph from graph1.txt
	//Data initialization


	vector<list<pair<int, int>>> Graph2(Nodes+2);
	vector<tuple<...>> Table2(Nodes+2);
	//Read in graph from graph2.txt
	//Data initialization
	

	BipartiteMatching(Graph2, Table2, Nodes, Nodes+1);

	return 0;
}
//The following is a sample screenshot.
/*
The maximum flow = 19
The following edges have scheduled flow as indicated:
The scheduled flow on edge (0, 1) = 10 out of capacity = 10
The scheduled flow on edge (0, 2) = 9 out of capacity = 10
The scheduled flow on edge (1, 3) = 4 out of capacity = 4
The scheduled flow on edge (1, 4) = 6 out of capacity = 8
The scheduled flow on edge (2, 4) = 9 out of capacity = 9
The scheduled flow on edge (3, 5) = 9 out of capacity = 10
The scheduled flow on edge (4, 3) = 5 out of capacity = 5
The scheduled flow on edge (4, 5) = 10 out of capacity = 10

The maximum matching = 5
The following matchings are selected:
(0, 8)
(1, 5)
(2, 6)
(3, 9)
(4, 7)
*/

//Input format for max flow problem in graph1.txt
/*
0 //source node
5 //sink node
6 //number of nodes
9 //number of edges
0 1 10 //A directed edge from node 0 to node 1 with weight 10 .
0 2 10
1 3 4
1 4 8
1 2 2
2 4 9
3 5 10
4 3 5
4 5 10
*/

//input format for bipartite matching in graph2.txt
/*
10 //Number of Nodes 0 ... 9
9 //Number of Edges
5 //L -- number of nodes on the left side;  0 ...L-1 are on the left side
5 //R -- number of nodes on the right side; L ... L+R-1 are on the right side
0 5 //An undirected edge connecting 0 to 5
0 7
0 8
1 5
2 6
2 7
3 8
3 9
4 7
*/