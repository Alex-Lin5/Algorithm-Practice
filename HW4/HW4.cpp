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
#include <map>
#include <queue>
#include <tuple>
#include <string>
#include <climits>

using namespace std;

//You will implement the following three functions.  No additional functions are allowed.
void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t);//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t);//Graph, Table, source, sink
int BFS(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t);
//Both BipartiteMatching and MaxFlow will call BFS.
//Return the flow on the path found by BFS or 0 if no path found

int main() {
	int source, sink;
  int Nodes, Edges;
	vector<list<pair<int, int>>> Graph1;
	vector<tuple<map<int, pair<int, int>>, bool>> Table1;//  Design the tuple. Remember that you will perform BFS
	
  string file1 = "graph1.txt";
  ifstream stream1(file1);
	if(!stream1) std::cout << endl << "File is not existed. " << file1;
	if(stream1.peek() == std::ifstream::traits_type::eof()) 
		std::cout << endl << "Stream reaches eof, file is empty. " << file1;
	//Read in graph from graph1.txt
	//Data initialization
	{
		int src, dst, weight;
		stream1 >> source >> sink;
		stream1 >> Nodes >> Edges;
		stream1 >> src;
		for(int i=0, j=0; i<Nodes; i++){
			list<pair<int,int>> temp;
			while(j<Edges && src==i){
				stream1 >> dst >> weight;
				temp.push_back(make_pair(dst,weight));
				stream1 >> src;
				j++;
			}
			// // sort edges based on weight
			// for(auto itr1=temp.begin(); itr1!=temp.end(); itr1++){
			// 	for(auto itr2=itr1; itr2!=temp.end(); itr2++){
			// 		if(itr2->second < itr1->second)
			// 			swap(*itr1, *itr2);
			// 	}
			// }
			Graph1.push_back(temp);
		}
		// table1
		Table1.clear();
		{
			int src, dst;
			for(int i=0; i<Nodes; i++){
				Table1.push_back(make_tuple(map<int,pair<int,int>>{}, false));
				// Table1.push_back(make_tuple(-1, false, INT_MAX, INT_MIN, -1));
				// current predecessor, visited, weight, capacity, last predecessor
			}
		}
	}

	
  stream1.close();
	// source = sink = 0;
	// Nodes = Edges = 0;
	{
		// print Graph1
		cout << endl << "Graph1:" << endl;
		int i=0;
		for(auto listt : Graph1){
			for(auto pr : listt){
				cout << i << " " << pr.first << " " << pr.second << endl;
			}
			i++;
		}
	}
	MaxFlow(Graph1, Table1, source, sink);



  string file2 = "graph2.txt";
  ifstream stream2(file2);
	if(!stream2) cout << endl << "File is not existed." << file2;
	if(stream2.peek() == std::ifstream::traits_type::eof()) 
		cout << endl << "Stream reaches eof, file is empty." << file2;
	//Read in graph from graph2.txt
	//Data initialization
	int Lnum, Rnum;
	stream2 >> Nodes >> Edges;
	stream2 >> Lnum >> Rnum;
	vector<list<pair<int, int>>> Graph2(Nodes+2);
	vector<tuple<map<int, pair<int, int>>, bool>> Table2(Nodes+2);
	for(int i=0; i<Edges; i++){
		int src, dst, wei;
		stream2 >> src >> dst >> wei;
		auto itr=Graph2[src].begin();
		for(; itr!=Graph2[src].end(); itr++){
			if(itr->first == dst) break;
		}
		if(itr == Graph2[src].end()) continue;
		Graph2[src].push_back(make_pair(dst, wei));
		Graph2[dst].push_back(make_pair(src, wei));
	}
  stream2.close();
	{
		// print Graph2
		cout << endl << "Graph2:" << endl;
		for(auto listt:Graph2){
			for(auto pr:listt){
				cout << pr.first << " " << pr.second << endl;
			}
		}
	}
	Nodes = Lnum+Rnum;
	BipartiteMatching(Graph2, Table2, Nodes, Nodes+1);
	return 0;
}

void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t){
	int match;
	// Initialize
	match = 0;
	T.clear();
	for(auto listt:G){
		for(auto pr:listt){
			int src, dst;
			src = pr.first;
			dst = pr.second;
			// T.push_back(make_tuple(-1, false, INT_MAX, INT_MIN));
		}
	}
	// Connecting

	// Print the result
	cout << endl << "The maximum matching = "<< match;
	if(match == 0){
		cout << endl << "No matching in the graph";
		return;
	}
	cout << endl << "The following matchings are selected:";
	// {
	// 	int edges = T.size();
	// 	for(int i=0; i<edges; i++){
	// 		int src, dst, wei;
	// 		src = get<0>(T[i]);
	// 		dst = get<1>(T[i]);
	// 		wei = get<2>(T[i]);
	// 		if(wei == 0) continue;
	// 		cout << endl << "(" << src << ", " << dst << ")";
	// 	}
	// }

}//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t){
	int flow = 0;
	// Initialize
	for(int i=0, size=G.size(); i<size; i++){
		list<pair<int,int>> temp;
		for(auto pr : G[i]){
			int dst, wei;
			dst = pr.first;
			wei = pr.second;
			temp.push_back(make_pair(dst, INT_MIN));
		}
		G.push_back(temp);
	}
	// Connect
	while(BFS(G, T, s, t)){
		int node = t;
		// print path
		cout << endl << "Current selected path is: " << node;
		// while(node != s){
		// 	// node = get<0>(T[node]);
		// 	// cout << "<-" << node;
		// }

		// update residual graph
		node = t;
		int stream = INT_MAX;
		// while(node != s){
		// 	// find single stream of this path
		// 	int src, dst, wei, cap;
		// 	dst = node;
		// 	src = get<0>(T[node]);
		// 	wei = get<2>(T[node]);
		// 	cap = get<3>(T[node]);
		// 	if(-cap < stream) stream = cap;
		// 	node = src;
		// }
		flow += stream;
		// while(node != s){
		// 	int src, dst, wei, cap;
		// 	dst = node;
		// 	src = get<0>(T[node]);
		// 	wei = get<2>(T[node]);
		// 	cap = get<3>(T[node]);			
		// 	auto itr = G[src+G.size()/2].begin();
		// 	for(; itr->second != dst; itr++);
		// 	itr->second += stream;
		// 	node = src;
		// }
	} 	

	// print result
	cout << endl << "The maximum flow = " << flow;
	if(flow <= 0){
		cout << endl << "No flow go through " << s << " to " << t;
		return;
	}
	cout << endl << "The following edges have scheduled flow as indicated:";
	// int edges = T.size();
	for(int i=0; i<G.size()/2; i++){
		int src, dst, weight, cap;
		src = i;
		auto itr1=G[i].begin();
		auto itr2=G[i+G.size()/2].begin();
		for(; itr1!=G[i].end(); itr1++, itr2++){
			if(itr1->first != itr2->first){
				cout << endl << "destiny node does not match. " << itr1->first << " !=" << itr2->first;
				break;
			}
			dst = itr1->first;
			weight = itr1->second;
			cap = itr2->second;
			if(cap+weight < 0){
				cout << endl << "Capacity is greater than limit: " << cap << " > " << weight;
				break;
			}
			cout << endl << "The scheduled flow on edge (" << src << ", " << dst;
			cout << ") = " << weight << "out of capacity = " << cap;
		}
	}
}//Graph, Table, source, sink

int BFS(vector<list<pair<int, int>>>& G, vector<tuple<map<int, pair<int, int>>, bool>>& T, int s, int t){
	queue<int> Q;
	// Initialize
	int Nodes = T.size();
	// T.clear();
	{
		int src, dst;
		for(int i=0; i<Nodes; i++){
			get<1>(T[i]) = false;
			// T.push_back(make_tuple(-1, false, INT_MAX, INT_MIN));
		}
	}
	Q.push(s);
	// Connecting
	while(!Q.empty()){
		int src = Q.front();
		Q.pop();
		if(get<1>(T[src]) == true) continue; // ignore visited node
		get<1>(T[src]) = true;
		vector<int> neib;
		// info from previous table
		{
			int dst, cap, wei;
			dst = get<4>(T[src]);
			cap = get<3>(T[src]);
			wei = get<2>(T[src]);
		}
		auto itr1=G[src].begin();
		auto itr2=G[src+G.size()/2].begin();
		for(; itr2!=G[src+G.size()/2].end(); itr1++, itr2++){
			int dst, cap, wei, rev;
			dst = itr2->first;
			cap = itr2->second;
			wei = itr1->second;
			if(cap == 0){
				// auto itr = G[dst];
				continue;
			} 
			neib.push_back(dst);
			// get<0>(T[dst]) = src;
			// get<2>(T[dst]) = wei;
			// get<3>(T[dst]) = cap;
		}
		// sort neighbors
		for(int i=0; i<neib.size(); i++){
			for(int j=i; j<neib.size(); j++){
				if(neib[i] > neib[j]) swap(neib[i], neib[j]);
			}
			Q.push(neib[i]);
		}
	}
	if(get<0>(T[t]) == -1) return 0;
	return 1;
}