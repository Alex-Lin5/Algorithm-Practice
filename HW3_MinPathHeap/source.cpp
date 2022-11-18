
//HW3 Due: 11:59pm, Friday, October 7.

//HW2A: Dijkstra's algorithm with HEAP (20 points)
//HW2B: Use the same design for Prim's algorithm (5 points)
//In HW2B, for each x->y edges, also create a y->x edge with the same weight
// Note that printing results is also performed in the functions.

//You need to use the same function parameters as described.
//You are not allowed to use any extra functions
//You are not allowed to define any class.


//Note that even though we can pick any node as starting node for Prim's algorithm,
//for grading purpose, we will use the same source node as in Dijkstra's algorithm for Prim's algorithm.


#include <iostream>
#include <vector>
#include <list>
using namespace std;


	void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<...>>& table, vector<tuple<...>> & heap, int source);//20 points
	void MST(vector<list<pair<int, int>>>& graph, vector<tuple<...>>& table, vector<tuple<...>> & heap, int source); //5 points


	int main() {

		vector<list<pair<int, int>>> graph;
		//your code to read in graph from "graph.txt"

		vector<tuple<...>> table;//define your tuple
		vector<tuple<...>> heap; //define your tuple


		


		//You might need to make some initialization setting for table and heap

		ShortestPath(graph, table, heap, source);//HW2A

		You might need to reset some data.

		MST(graph, table, heap, source);//HW2B
		
	}
	void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<...>>& table, vector<tuple<...>> & heap, int source) {

		//Your code  -- HW2A 20 pts
	}
	void MST(vector<list<pair<int, int>>>& graph, vector<tuple<...>>& table, vector<tuple<...>> & heap, int source) {

		//Your code -- HW2B 5 pts
	}


	//sample input file graph.txt
	/*
	0 //source node
	6 //# of nodes in graph
	12 //# of edges in graph
	0 5 16//an edge from node 0 to node 5 with a weight (cost) of 16
	0 4 15
	0 2 4
	0 3 12
	0 1 9
	1 3 3
	1 5 2
	2 3 14
	2 1 3
	3 4 4
	4 5 1
	5 3 2
	*/

	//The following is a sample output format.  For Dijkstra's algorithm, the graph is interpreted as a directed graph.
	//For Prim's algorithm, the graph is interpreted as an un-directed (i.e., bi-directional) graph.
	/*
	For the shortest paths using Dijkstra's algorithm:
	The cost from 1 to 0 is infinity and no paths exist!
	The cost from 1 to 1 is 0 and the path is   1
	The cost from 1 to 2 is infinity and no paths exist!
	The cost from 1 to 3 is 3 and the path is   3<-1
	The cost from 1 to 4 is 7 and the path is   4<-3<-1
	The cost from 1 to 5 is 2 and the path is   5<-1

	For the minimum spanning tree using Prim's algorithm:
	The selected edges are:
	0 2 4
	2 1 3
	3 5 2
	4 5 1
	5 1 2
	The overall cost is 12 .
	*/
