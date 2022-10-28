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

using namespace std;


void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int,int,bool,int>>& table, vector<tuple<int,int>>& heap, int source);//20 points
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int,int,bool,int>>& table, vector<tuple<int,int>>& heap, int source); //5 points


int main() {

	int numNodes;
	int numEdges;
	int source;

	ifstream lcInput;
	lcInput.open("graph.txt");

	if (!lcInput.is_open())
	{
		std::cout << "File not found" << std::endl;
		return 0;
	}

	lcInput >> source >> numNodes >> numEdges;

	//pair<DestNode, EdgeWeight>
	vector<list<pair<int, int>>> graph(numNodes);
	vector<list<pair<int, int>>> ugraph(numNodes);

	for (int i = 0; i < numEdges; i++)
	{
		int current, dest, weight;
		lcInput >> current >> dest >> weight;
		graph[current].push_back(make_pair(dest, weight));
		ugraph[current].push_back(make_pair(dest, weight));
		ugraph[dest].push_back(make_pair(current, weight));
	}

	// <cost,from,visited,heapIdx>
	vector<tuple<int, int, bool, int>> table;
	// <id, value>
	vector<tuple<int, int>> heap;

	//initalize table and hash
	for (int i = 0; i < numNodes; i++)
	{
		table.push_back(tuple<int, int, bool,int>(INT_MAX, -1, false,i));
		heap.push_back(tuple<int, int>(i, INT_MAX));
	}

	ShortestPath(graph, table, heap, source);//HW2A

	//re-initalize table and hash
	table.clear();
	heap.clear();
	for (int i = 0; i < numNodes; i++)
	{
		table.push_back(tuple<int, int, bool, int>(INT_MAX, -1, false, i));
		heap.push_back(tuple<int, int>(i, INT_MAX));
	}

	MST(ugraph, table, heap, source);//HW2B

}
void ShortestPath(vector<list<pair<int, int>>>& graph, vector<tuple<int,int,bool,int>>& table, vector<tuple<int,int>>& heap, int source) {

	//Set table values for source to 0
	get<0>(table[source]) = 0;
	get<1>(table[source]) = source;

	//set source value in heap to 0
	get<1>(heap[source]) = 0;

	//adjust heap to have correct value
	// since all other node should be INF 
	// we can auto swap and will be correct
	swap(heap[source], heap[0]);

	while (!heap.empty())
	{
		//get value on top of heap and adjust
		int selected = get<0>(heap[0]);
		swap(heap[0], heap[heap.size()-1]);
		heap.pop_back();
		int i = 0;
		int parentIdx = 0;
		while (heap.size() > 1)
		{
			//Get Indexes of children nodes
			int leftIdx = 2 * parentIdx + 1;
			int rightIdx = 2 * parentIdx + 2;

			//terminate if at the leaf 
			if (leftIdx > heap.size()-1 && rightIdx > heap.size()-1) break;
			if (rightIdx > heap.size()-1) rightIdx = heap.size()-1;
			
			//Get node values
			int childLeft = get<1>(heap[leftIdx]);
			int childRight = get<1>(heap[rightIdx]);
			int parent = get<1>(heap[parentIdx]);

			if (parent > childLeft && childLeft <= childRight) {
				swap(heap[parentIdx], heap[leftIdx]);
				parentIdx = leftIdx;
			}
			else if (parent > childRight && childRight < childLeft)
			{
				swap(heap[parentIdx], heap[rightIdx]);
				parentIdx = rightIdx;	
			}
			else
			{
				//heap is correct and break loop
				break;
			}
		}
		//reset table indexes after delete operation
		for (int i = 0; i < heap.size(); i++) {
			get<3>(table[get<0>(heap[i])]) = i;
		}
		//Mark node as visited
		get<2>(table[selected]) = true;

		for (auto neighbor : graph[selected])
		{
			int id = get<0>(neighbor);
			//If not visited
			if (!get<2>(table[id]))
			{
				int edge = get<1>(neighbor);
				int neighborCost = get<0>(table[id]);
				int currentCost = get<0>(table[selected]);

				if (currentCost + edge < neighborCost && currentCost != INT_MAX)
				{
					get<0>(table[id]) = currentCost + edge;
					get<1>(table[id]) = selected;
					get<1>(heap[get<3>(table[id])]) = currentCost + edge;
				}
			}
		}

		//After adjsuting all neighbor values adjust the heap
		for (int j = floor(heap.size() / 2) - 1; j >= 0; j--)
		{
			parentIdx = j;
			while (true)
			{
				//Get Indexes of children nodes
				int leftIdx = 2 * parentIdx + 1;
				int rightIdx = 2 * parentIdx + 2;

				//terminate if at the leaf 
				if (leftIdx > heap.size()-1 && rightIdx > heap.size()-1) break;
				if (rightIdx > heap.size()-1) rightIdx = heap.size()-1;

				//Get node values
				int childLeft = get<1>(heap[leftIdx]);
				int childRight = get<1>(heap[rightIdx]);
				int parent = get<1>(heap[parentIdx]);

				if (parent > childLeft && childLeft <= childRight) {
					swap(heap[parentIdx], heap[leftIdx]);
					get<3>(table[get<0>(heap[parentIdx])]) = leftIdx;
					get<3>(table[get<0>(heap[leftIdx])]) = parentIdx;
					parentIdx = leftIdx;
				}
				else if (parent > childRight && childRight < childLeft)
				{
					swap(heap[parentIdx], heap[rightIdx]);
					get<3>(table[get<0>(heap[parentIdx])]) = rightIdx;
					get<3>(table[get<0>(heap[rightIdx])]) = parentIdx;
					parentIdx = rightIdx;
				}
				else
				{
					//heap is correct and break loop
					break;
				}
			}
		}
		
	}
	//Print results
	cout << "For the shortest paths using Djkstra's algorithm:\n";
	for (int i = 0; i < table.size(); i++) {
		
		cout << "The cost from " << source << " to " << i << " is ";
		if (get<0>(table[i]) == INT_MAX) {
			cout << "is infinity and no paths exist!\n";
		}
		else {
			cout << get<0>(table[i]) << " and the path is   " << i ;
			if (i != source) {
				int from = get<1>(table[i]);
				while (from != source || from == -1) {
					cout << "<-" << from;
					from = get<1>(table[from]);

				}
				cout << "<-" << source << endl;
			}
			else {
				cout << endl;
			}
		}
	}
}
void MST(vector<list<pair<int, int>>>& graph, vector<tuple<int,int,bool,int>>& table, vector<tuple<int,int>>& heap, int source) {

	//Set table values for source to 0
	get<0>(table[source]) = 0;
	get<1>(table[source]) = source;

	//set source value in heap to 0
	get<1>(heap[source]) = 0;

	//adjust heap to have correct value
	// since all other node should be INF 
	// we can auto swap and will be correct
	swap(heap[source], heap[0]);

	while (!heap.empty())
	{
		//get value on top of heap and adjust
		int selected = get<0>(heap[0]);
		swap(heap[0], heap[heap.size() - 1]);
		heap.pop_back();
		int i = 0;
		int parentIdx = 0;
		while (heap.size() > 1)
		{
			//Get Indexes of children nodes
			int leftIdx = 2 * parentIdx + 1;
			int rightIdx = 2 * parentIdx + 2;

			//terminate if at the leaf 
			if (leftIdx > heap.size() - 1 && rightIdx > heap.size() - 1) break;
			if (rightIdx > heap.size() - 1) rightIdx = heap.size() - 1;

			//Get node values
			int childLeft = get<1>(heap[leftIdx]);
			int childRight = get<1>(heap[rightIdx]);
			int parent = get<1>(heap[parentIdx]);

			if (parent >= childLeft && childLeft <= childRight) {
				swap(heap[parentIdx], heap[leftIdx]);
				parentIdx = leftIdx;
			}
			else if (parent >= childRight && childRight < childLeft)
			{
				swap(heap[parentIdx], heap[rightIdx]);
				parentIdx = rightIdx;
			}
			else
			{
				//heap is correct and break loop
				break;
			}
		}
		//reset table indexes after delete operation
		for (int i = 0; i < heap.size(); i++) {
			get<3>(table[get<0>(heap[i])]) = i;
		}
		//Mark node as visited
		get<2>(table[selected]) = true;

		for (auto neighbor : graph[selected])
		{
			int id = get<0>(neighbor);
			//If not visited
			if (!get<2>(table[id]))
			{
				int edge = get<1>(neighbor);
				int neighborCost = get<0>(table[id]);

				if (edge < neighborCost)
				{
					get<0>(table[id]) = edge;
					get<1>(table[id]) = selected;
					get<1>(heap[get<3>(table[id])]) = edge;
				}
			}
		}

		//After adjsuting all neighbor values adjust the heap
		for (int i = floor(heap.size() / 2) - 1; i >= 0; i--)
		{
			parentIdx = i;
			while (true)
			{
				//Get Indexes of children nodes
				int leftIdx = 2 * parentIdx + 1;
				int rightIdx = 2 * parentIdx + 2;

				//terminate if at the leaf 
				if (leftIdx > heap.size() - 1 && rightIdx > heap.size() - 1) break;
				if (rightIdx > heap.size() - 1) rightIdx = heap.size() - 1;

				//Get node values
				int childLeft = get<1>(heap[leftIdx]);
				int childRight = get<1>(heap[rightIdx]);
				int parent = get<1>(heap[parentIdx]);

				if (parent >= childLeft && childLeft <= childRight) {
					swap(heap[parentIdx], heap[leftIdx]);
					get<3>(table[get<0>(heap[parentIdx])]) = leftIdx;
					get<3>(table[get<0>(heap[leftIdx])]) = parentIdx;
					parentIdx = leftIdx;
				}
				else if (parent >= childRight && childRight < childLeft)
				{
					swap(heap[parentIdx], heap[rightIdx]);
					get<3>(table[get<0>(heap[parentIdx])]) = rightIdx;
					get<3>(table[get<0>(heap[rightIdx])]) = parentIdx;
					parentIdx = rightIdx;
				}
				else
				{
					//heap is correct and break loop
					break;
				}
			}
		}

	}

	int cost = 0;
	cout << "\nFor the minumum spanning tree using Prim's algorithm:\nThe selected edges are:\n";
	for (int i = 0; i < table.size(); i++) {
		if (get<0>(table[i]) == 0) continue;
		cout << i << " " << get<1>(table[i]) << " " << get<0>(table[i]) << endl;
		cost += get<0>(table[i]);
	}
	cout << "The overall cost is " << cost << "\n\n";
}