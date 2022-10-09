
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
#include <climits>

using namespace std;
void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source);//20 points
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source); //5 points

int main() {
	// cout << endl << "C++ default standard in g++ compiler is: " << __cplusplus << endl;

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

  vector<tuple<int, int, bool, int>> table;//define your tuple
  vector<tuple<int, int>> heap; //define your tuple

  In >> source >> nodes >> edges;
	In >> src;
	// source = 3;
	for(int i=0, j=0; i<nodes; i++){
		dst = weight = -1;
		list<pair<int, int>> temp;
		while(src == i && j < edges){
			In >> dst >> weight;
			temp.push_back(make_pair(dst, weight));
			In >> src;
			j++;
			// cout << endl << dst << " " << weight;
		}		
		graph.push_back(temp);
	}
	In.close();
	if(graph.size() == 0) cout << endl << "graph is empty" << endl;

	// // print the graph
	// {
	// 	auto itr1 = graph.begin();
	// 	int i = 0;
	// 	while(itr1 != graph.end()){ // list
	// 		auto itr2 = itr1->begin();
	// 		while(itr2 != itr1->end()){ // pair
	// 			cout << endl << i << " " << itr2->first << " " << itr2->second;
	// 			itr2++;
	// 		}
	// 		i++;
	// 		itr1++;
	// 	}
	// }

  //You might need to make some initialization setting for table and heap
	// cout << endl << "INT_MAX=" << INT_MAX;
  ShortestPath(graph, table, heap, source);//HW2A

  // You might need to reset some data.
	table.clear();
	heap.clear();
	// make bi-directional graph
	{
		auto itr1 = graph.begin();
		int src = 0;
		while(itr1 != graph.end()){
			auto itr2 = itr1->begin();
			while(itr2 != itr1->end()){
				int dst = itr2->first;
				int weight = itr2->second;
				auto pos = find(graph[dst].begin(), graph[dst].end(), make_pair(src, weight));
				if(pos == graph[dst].end())
					graph[dst].push_back(make_pair(src, weight));
				itr2++;
			}
			itr1++;
			src++;
		}
	}
	// // print the graph
	// {
	// 	auto itr1 = graph.begin();
	// 	int i = 0;
	// 	while(itr1 != graph.end()){ // list
	// 		auto itr2 = itr1->begin();
	// 		while(itr2 != itr1->end()){ // pair
	// 			cout << endl << i << " " << itr2->first << " " << itr2->second;
	// 			itr2++;
	// 		}
	// 		i++;
	// 		itr1++;
	// 	}
	// }

  MST(graph, table, heap, source);//HW2B
  
	return 0;
}

void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source) {
	cout << endl << "For the shortest paths using Dijkstra's algorithm:";
	if(source < 0){
		cout << endl << "source node is a negtive value. source=" << source << endl;
		return;
	}
	// initialization
	heap.push_back(make_tuple(source, 0));
	for(int i=0; i<graph.size(); i++){
		if(i == source){
			table.push_back(make_tuple(0, source, false, 0));
			continue;
		} else if(i < source){
			table.push_back(make_tuple(INT_MAX, -1, false, i+1));
		} else if(i > source){
			table.push_back(make_tuple(INT_MAX, -1, false, i));
		}
		// (cost, from, visited, heapIndex)
		heap.push_back(make_tuple(i, INT_MAX));
		// (id, cost)
	}

	// connecting
	while(!heap.empty()){
		int node = get<0>(heap[0]); // select minimum cost unvisited neighbor
		if(get<2>(table[node])) continue; // node is visited
		else get<2>(table[node]) = true;
		// // print heap
		// cout << endl << "heap: ";
		// for(int i=0; i<heap.size(); i++){
		// 	cout << "(" << get<0>(heap[i]) << "," << get<1>(heap[i]) << ") ";
		// }
		// heapify top down
		get<3>(table[node]) = -1;
		get<3>(table[get<0>(heap.back())]) = 0;
		swap(heap[0], heap.back());
		heap.pop_back();
		if(get<0>(table[node]) == INT_MAX) continue; // Do not operate on unconnected node
		int minnd = 0;
		int size = heap.size();
		while(minnd >= 0 && minnd < size){
			int parentC = get<1>(heap[minnd]);
			int leftchildC, rightchildC;
			if(2*minnd+1 < size)
				leftchildC = get<1>(heap[2*minnd+1]);
			else leftchildC = INT_MAX;
			if(2*minnd+2 < size)
				rightchildC = get<1>(heap[2*minnd+2]);
			else rightchildC = INT_MAX;
			if(leftchildC < parentC && leftchildC <= rightchildC){
				// swap nodes in heap
				swap(heap[minnd], heap[2*minnd+1]);
				// swap heapIndex in table
				swap(get<3>(table[get<0>(heap[minnd])]), 
					get<3>(table[get<0>(heap[2*minnd+1])]));
				minnd = 2*minnd+1;
			} else if(rightchildC < parentC && rightchildC <= leftchildC){
				swap(heap[minnd], heap[2*minnd+2]);
				swap(get<3>(table[get<0>(heap[minnd])]), 
					get<3>(table[get<0>(heap[2*minnd+2])]));
				minnd = 2*minnd+2;
			} else break;
		}
		
		auto itr = graph[node].begin();
		while(itr != graph[node].end()){
			int neighbor = itr->first;
			int weight = itr->second;
			itr++;
			if(get<2>(table[neighbor])) continue; // run only on unvisited neighbor
			int costThis = get<0>(table[node]);
			int costNei = get<0>(table[neighbor]);
			if(costThis+weight < costNei){
				if(costThis+weight < 0)
					get<0>(table[neighbor]) = weight;
				else
					get<0>(table[neighbor]) = costThis + weight;
				get<1>(table[neighbor]) = node;
				// heapify bottom up
				int minhp = get<3>(table[neighbor]);
				get<1>(heap[minhp]) = costThis + weight;
				while(minhp > 0){
					int childW, parentW;
					childW = get<1>(heap[minhp]);
					if((minhp-1)/2 >= 0)
						parentW = get<1>(heap[(minhp-1)/2]);
					else parentW = -1;
					if(childW < parentW){
						// swap nodes in heap
						swap(heap[minhp], heap[(minhp-1)/2]);
						// swap heapIndex in table
						swap(get<3>(table[get<0>(heap[minhp])]), 
							get<3>(table[get<0>(heap[(minhp-1)/2])]));
						minhp = (minhp-1)/2;
					} else break;
				}
			}
		}
	}

	// print the result from table
	for(int i=0; i<graph.size(); i++){
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
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int, int, bool, int>>& table, vector<tuple<int, int>>& heap, int source) {
	cout << endl << endl << "For the minimum spanning tree using Prim's algorithm:";
	if(source < 0){
		cout << endl << "source node is a negtive value. source=" << source << endl;
		return;
	}
	// initialization
	heap.push_back(make_tuple(source, 0));
	for(int i=0; i<graph.size(); i++){
		if(i == source){
			table.push_back(make_tuple(0, source, false, 0));
			continue;
		} else if(i < source){
			table.push_back(make_tuple(INT_MAX, -1, false, i+1));
		} else if(i > source){
			table.push_back(make_tuple(INT_MAX, -1, false, i));
		}
		// (cost, from, visited, heapIndex)
		heap.push_back(make_tuple(i, INT_MAX));
		// (id, cost)
	}
	// get<0>(table[source]) = 0;
	// get<1>(table[source]) = source;

	// connecting
	while(!heap.empty()){
		int node = get<0>(heap[0]); // select minimum cost unvisited neighbor
		if(get<2>(table[node])) continue; // node is visited
		else get<2>(table[node]) = true;
		// // print heap
		// cout << endl << "heap: ";
		// for(int i=0; i<heap.size(); i++){
		// 	cout << "(" << get<0>(heap[i]) << "," << get<1>(heap[i]) << ") ";
		// }
		// heapify top down
		get<3>(table[node]) = -1;
		get<3>(table[get<0>(heap.back())]) = 0;
		swap(heap[0], heap.back());
		heap.pop_back();
		int minnd = 0;
		int size = heap.size();
		while(minnd >= 0 && minnd < size){
			int parentC = get<1>(heap[minnd]);
			int leftchildC, rightchildC;
			if(2*minnd+1 < size)
				leftchildC = get<1>(heap[2*minnd+1]);
			else leftchildC = INT_MAX;
			if(2*minnd+2 < size)
				rightchildC = get<1>(heap[2*minnd+2]);
			else rightchildC = INT_MAX;
			if(leftchildC < parentC && leftchildC <= rightchildC){
				// swap nodes in heap
				swap(heap[minnd], heap[2*minnd+1]);
				// swap heapIndex in table
				swap(get<3>(table[get<0>(heap[minnd])]), 
					get<3>(table[get<0>(heap[2*minnd+1])]));
				minnd = 2*minnd+1;
			} else if(rightchildC < parentC && rightchildC <= leftchildC){
				swap(heap[minnd], heap[2*minnd+2]);
				swap(get<3>(table[get<0>(heap[minnd])]), 
					get<3>(table[get<0>(heap[2*minnd+2])]));
				minnd = 2*minnd+2;
			} else break;
		}
		
		auto itr = graph[node].begin();
		while(itr != graph[node].end()){
			int neighbor = itr->first;
			int weight = itr->second;
			itr++;
			if(get<2>(table[neighbor])) continue; // run only on unvisited neighbor
			else if(get<3>(table[neighbor]) == -1) continue; // do not consider backward traces
			int costNei = get<0>(table[neighbor]);
			if(weight < costNei){
				get<0>(table[neighbor]) = weight;
				get<1>(table[neighbor]) = node;
				// heapify bottom up
				int minhp = get<3>(table[neighbor]);
				get<1>(heap[minhp]) = weight;
				while(minhp > 0){
					int childW, parentW;
					childW = get<1>(heap[minhp]);
					if((minhp-1)/2 >= 0)
						parentW = get<1>(heap[(minhp-1)/2]);
					else parentW = -1;
					if(childW < parentW){
						// swap nodes in heap
						swap(heap[minhp], heap[(minhp-1)/2]);
						// swap heapIndex in table
						swap(get<3>(table[get<0>(heap[minhp])]), 
							get<3>(table[get<0>(heap[(minhp-1)/2])]));
						minhp = (minhp-1)/2;
					} else break;
				}
			}
		}
	}

	// print MST
	cout << endl << "The selected edges are:";
	{
		int sum = 0;
		for(int i=0; i<graph.size(); i++){
			if(i == source) continue;
			cout << endl << i << " " << get<1>(table[i]) << " " << get<0>(table[i]);
			sum += get<0>(table[i]);
		}
		cout << endl << "The overall cost is " << sum;
	}
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
