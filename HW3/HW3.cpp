
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
#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <stack>
#include <functional>
#include <climits>
#include <type_traits>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE MAX_PATH

using namespace std;
void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool>>& table, vector<tuple<int, int>>& heap, int source);//20 points
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool>>& table, vector<tuple<int, int>>& heap, int source); //5 points

int main() {
	TCHAR buffer[BUFSIZE];
	DWORD dwRet = GetCurrentDirectory(BUFSIZE, buffer);
	cout << endl << "Current directory is: "<< buffer << endl;

	cout << endl << "C++ default standard in g++ compiler is: " << __cplusplus << endl;

	ifstream In("graph.txt");
	if(!In) cout << endl << "File is not existed.";
	if(In.peek() == std::ifstream::traits_type::eof()) 
		cout << endl << "Stream reaches eof, file is empty.";
	// if(std::filesystem::is_empty("graph.txt")) cout << endl << "File is empty indicated by filesystem.";
	// if(is_empty<ifstream>::In) cout << endl << "File is empty.";
	// if(is_empty(In)) cout << endl << "File is empty indicated by filesystem.";
	// if(is_empty<In>::value)
	
	// check input stream data
	// char data;
	// while(In >> data){
	// 	cout << data;
	// }
  
	int source;
	int nodes, edges;
	int src, dst, weight;
  vector<list<pair<int, int>>> graph;
  //your code to read in graph from "graph.txt"

  vector<tuple<int, int, bool>> table;//define your tuple
  vector<tuple<int, int>> heap; //define your tuple

  In >> source >> nodes >> edges;
	In >> src;
	for(int i=0; i<nodes; i++){
		dst = weight = -1;
		list<pair<int, int>> temp {};
		// for(In >> src; src == i;){
		// for(; src == i; In >> src){
		while(src && src == i){
			In >> dst >> weight;
			temp.push_back(make_pair(dst, weight));
			In >> src;
		}
		graph.push_back(temp);
	}
	In.close();
	if(graph.size() == 0) cout << endl << "graph is empty" << endl;

	// print the graph
	auto itr1 = graph.begin();
	while(itr1 != graph.end()){ // list
		auto itr2 = itr1->begin();
		while(itr2 != itr1->end()){ // pair
			cout << endl << source << " " << itr2->first << " " << itr2->second;
			itr2++;
		}
		itr1++;
		src++;
	}

  //You might need to make some initialization setting for table and heap

  ShortestPath(graph, table, heap, source);//HW2A

  // You might need to reset some data.

  MST(graph, table, heap, source);//HW2B
  
	return 0;
}
void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool>>& table, vector<tuple<int, int>>& heap, int source) {
	cout << endl << "For the shortest paths using Dijkstra's algorithm:";
	// initialization
	int nodes;
	nodes = graph.size();
	for(int i=0; i<nodes; i++){
		table.push_back(make_tuple(INT_MAX, -1, false));
		// (cost, from, visited)
	}
	// if(source == NULL){
	// 	cout << endl << "source node is not existed." << endl;
	// 	return;
	// } else 
	if(source < 0){
		cout << endl << "source node is a negtive value. source=" << source << endl;
		return;
	}
	get<0>(table[source]) = 0;
	get<1>(table[source]) = source;
	get<2>(table[source]) = true;

	// connecting
	stack<int> S;
	S.push(source);
	while(!S.empty()){
		int node = S.top();
		S.pop();
		if(get<2>(table[node])) continue; // node is visited
		else get<2>(table[node]) = true;
		
		int neighborMin{-1};
		auto itr = graph[node].begin();
		while(itr != graph[node].end()){
			// int neighbor = itr->first;
			// int weight = itr->second;
			// int costThis = get<0>(table[node]);
			// int costNei = get<0>(table[neighbor]);
			int neighbor = ref(itr->first);
			if(get<2>(table[neighbor])) continue; // run only on unvisited neighbor
			else S.push(neighbor);
			int weight = ref(itr->second);
			int costThis = ref(get<0>(table[node]));
			int costNei = ref(get<0>(table[neighbor]));
			if(costThis+weight < costNei){
				costNei = costThis + weight;
				get<1>(table[neighbor]) = node;
				neighborMin = neighbor;
			}
		}
		if(neighborMin == -1) continue;
		else S.push(neighborMin);
	}

	// print the result from table
	for(int i=0; i<nodes; i++){
		cout << endl << "The cost from " << source << " to " << i << " is ";
		if(get<1>(table[i]) == -1){
			cout << "infinity and no paths exist!";
		} else {
			cout << get<0>(table[i]) << " and the path is   ";
			int node{i};
			cout << i;
			while(node != source){
				node = get<1>(table[node]);
				cout << "<-" << node;
			}
		}

	}


  //Your code  -- HW2A 20 pts
}
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool>>& table, vector<tuple<int, int>>& heap, int source) {
	cout << endl << "For the minimum spanning tree using Prim's algorithm:";
	if(!source){
		cout << endl << "source node is not existed." << endl;
		return;
	} else if(source < 0){
		cout << endl << "source node is a negtive value." << endl;
		return;
	}
	cout << endl << "The selected edges are:";

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
