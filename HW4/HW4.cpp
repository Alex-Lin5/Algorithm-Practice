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
#include <string>

using namespace std;

//You will implement the following three functions.  No additional functions are allowed.
void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<int, int, int>>& T, int s, int t);//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<int, int, int>>& T, int s, int t);//Graph, Table, source, sink
int BFS(vector<list<pair<int, int>>>& G, vector<tuple<int, int, int>>& T, int s, int t);
//Both BipartiteMatching and MaxFlow will call BFS.
//Return the flow on the path found by BFS or 0 if no path found

int main() {
	int source, sink;
  int Nodes;
	vector<list<pair<int, int>>> Graph1;
	vector<tuple<int, int, int>> Table1;//  Design the tuple. Remember that you will perform BFS
	
  string file1 = "graph1.txt";
  ifstream stream1(file1);
	if(!stream1) cout << endl << "File is not existed. " << file1;
	if(stream1.peek() == std::ifstream::traits_type::eof()) 
		cout << endl << "Stream reaches eof, file is empty. " << file1;

	//Read in graph from graph1.txt
	//Data initialization
  stream1.close();
	MaxFlow(Graph1, Table1, source, sink);



	vector<list<pair<int, int>>> Graph2(Nodes+2);
	vector<tuple<int, int, int>> Table2(Nodes+2);
	//Read in graph from graph2.txt
	//Data initialization
  string file2 = "graph2.txt";
  ifstream stream2(file2);
	if(!stream2) cout << endl << "File is not existed." << file2;
	if(stream2.peek() == std::ifstream::traits_type::eof()) 
		cout << endl << "Stream reaches eof, file is empty." << file2;
  stream2.close();
	BipartiteMatching(Graph2, Table2, Nodes, Nodes+1);

	return 0;
}
