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
#include <tuple>
#include <string>
#include <climits>

using namespace std;

//You will implement the following three functions.  No additional functions are allowed.
void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<int, bool>>& T, int s, int t);//Graph, Table, source, sink
void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<int, bool>>& T, int s, int t);//Graph, Table, source, sink
int BFS(vector<list<pair<int, int>>>& Gcom, vector<list<pair<int, int>>>& Gup, vector<tuple<int, bool>>& T, int s, int t);
//Both BipartiteMatching and MaxFlow will call BFS.
//Return the flow on the path found by BFS or 0 if no path found

int main() {
	int source, sink;
  int Nodes, Edges;
	
  string file1 = "graph1.txt";
  ifstream stream1(file1);
	if(!stream1) std::cout << endl << "File is not existed. " << file1;
	if(stream1.peek() == std::ifstream::traits_type::eof()) 
		std::cout << endl << "Stream reaches eof, file is empty. " << file1;
	//Read in graph from graph1.txt
	//Data initialization
	
	stream1 >> source >> sink;
	stream1 >> Nodes >> Edges;
	vector<list<pair<int, int>>> Graph1(Nodes);
	vector<tuple<int, bool>> Table1;//  Design the tuple. Remember that you will perform BFS
	for(int i=0; i<Edges; i++){
		int src, dst, wei;	
		stream1 >> src >> dst >> wei;
		Graph1[src].push_back(make_pair(dst, wei));
		Graph1[dst].push_back(make_pair(src, -wei));
	}
	// sort edges
	for(int i=0; i<Graph1.size(); i++){ // O(E^2)
		for(auto itr1=Graph1[i].begin(); itr1!=Graph1[i].end(); itr1++){
			for(auto itr2=itr1; itr2!=Graph1[i].end(); itr2++){
				if(itr1->first > itr2->first)
					swap(*itr1, *itr2);
			}
		}
	}
	// table1
	{
		for(int i=0; i<Nodes; i++){
			Table1.push_back(make_tuple(-1, false));
			// from, visited
		}
	}
	

	
  stream1.close();
	// source = 4;
	// sink = 5;
	// // print Graph1
	// cout << endl << "Graph1:" << endl;
	// for(int i=0; i<Graph1.size(); i++){
	// 	for(auto pr : Graph1[i]){
	// 		cout << i << " " << pr.first << " " << pr.second << endl;
	// 	}
	// }
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
	vector<tuple<int, bool>> Table2(Nodes+2);
	for(int i=0; i<Edges; i++){
		int src, dst;
		stream2 >> src >> dst;
		Graph2[src].push_back(make_pair(dst, 1));
		Graph2[dst].push_back(make_pair(src, 1));
	}
	for(int i=0; i<Lnum; i++){
		Graph2[Graph2.size()-2].push_back(make_pair(i, 1));
	}
	for(int i=0; i<Rnum; i++){
		Graph2.back().push_back(make_pair(i+Lnum, 1));
		Graph2[i+Lnum].push_back(make_pair(Graph2.size()-1, 1));
	}	
  stream2.close();
	// sort edges
	for(int i=0; i<Graph2.size(); i++){ // O(E^2)
		for(auto itr1=Graph2[i].begin(); itr1!=Graph2[i].end(); itr1++){
			for(auto itr2=itr1; itr2!=Graph2[i].end(); itr2++){
				if(itr1->first > itr2->first)
					swap(*itr1, *itr2);
			}
		}
	}
	// Table2
	for(int i=0; i<Nodes+2; i++){
		Table2[i] = make_tuple(-1, false);
	}
	// // print Graph2
	// cout << endl << endl << "Graph2:" << endl;
	// for(int i=0; i<Graph2.size(); i++){
	// 	int src, dst;
	// 	src = i;
	// 	for(auto pr : Graph2[src]){
	// 		dst = pr.first;
	// 		cout << endl << src << " " << dst;
	// 	}
	// }
	Nodes = Lnum+Rnum;
	BipartiteMatching(Graph2, Table2, Nodes, Nodes+1);
	return 0;
}

void BipartiteMatching(vector<list<pair<int, int>>>& G, vector<tuple<int, bool>>& T, int s, int t){
	int match;
	int Lnum, Rnum;
	vector<list<pair<int, int>>> Gup(G.size());
	// Initialize
	Lnum = G[s].size();
	Rnum = G[t].size();
	match = 0;
	for(int i=0, size=G.size(); i<size; i++){ // O(E)
		for(auto pr : G[i]){
			int dst, wei;
			dst = pr.first;
			Gup[i].push_back(make_pair(dst, -1));
		}
	}
	// Connecting
	while(BFS(G, Gup, T, s, t)){ // O(VE)*O(E)
		int node;
		// // print path
		// node = t;
		// cout << endl << "Current selected path is: " << node;
		// while(node != s){
		// 	node = get<0>(T[node]);
		// 	cout << "<-" << node;
		// }

		// update residual graph
		node = t;
		while(node != s){ // O(E)
			int src, dst;
			dst = node;
			src = get<0>(T[dst]);
			for(auto itr=Gup[src].begin(); itr!=Gup[src].end(); itr++){
				if(itr->first == dst){
					itr->second = 0;
					break;
				}
			}
			for(auto itr=Gup[dst].begin(); itr!=Gup[dst].end(); itr++){
				if(itr->first == src){
					itr->second = -1;
					break;
				} 
			}

			node = src;
		}
		match += 1;
	}
	// Print the result
	cout << endl << endl << "The maximum matching = "<< match;
	if(match == 0){
		cout << endl << "No matching in the graph";
		return;
	}
	cout << endl << "The following matchings are selected:";
	for(int i=0; i<G.size()-2; i++){ // O(V)
		int src, dst, dir;
		src = i;
		for(auto itr=Gup[src].begin(); itr!=Gup[src].end(); itr++){ // O(E)
				dst = itr->first;
				dir = itr->second;
				if(dir < 0) continue;
				else if(dst == t) continue;
				cout << endl << "(" << src << ", " << dst << ")";
				break;
		}
	}
}//Graph, Table, source, sink

void MaxFlow(vector<list<pair<int, int>>>& G, vector<tuple<int, bool>>& T, int s, int t){
	int flow = 0;
	vector<list<pair<int,int>>> Gup(G.size());
	// Initialize
	for(int i=0, size=G.size(); i<size; i++){ // O(E)
		for(auto pr : G[i]){
			int dst, wei;
			dst = pr.first;
			wei = pr.second;
			if(wei < 0) continue;
			Gup[i].push_back(make_pair(dst, -wei));
		}
	}
	// Connect
	while(1){ // O(VE)
		int node = t;
		// find max stream in current path
		int stream = BFS(G, Gup, T, s, t);
		if(stream <= 0) break;

		// // print path
		// node = t;
		// cout << endl << "Current selected path is: " << node;
		// while(node != s){
		// 	node = get<0>(T[node]);
		// 	cout << "<-" << node;
		// }
		// cout << "\t\t" << "stream=" << stream;
		// update residual graph
		flow += stream;
		node = t;
		while(node != s){
			int src, dst, wei, cap;
			dst = node;
			src = get<0>(T[dst]);
			for(auto itr=Gup[src].begin(); itr!=Gup[src].end(); itr++){ // O(E)
				if(itr->first == dst){
					cap = itr->second;
					itr->second += stream;
					break;
				}
			}
			for(auto itr=Gup[dst].begin(); itr!=Gup[dst].end(); itr++){ // O(E)
				if(itr->first == src){
					cap = itr->second;
					itr->second -= stream;
					break;
				} 
			}
			node = src;
		}
	} 	

	// print result
	cout << endl << endl << "The maximum flow = " << flow;
	if(flow <= 0){
		cout << endl << "No flow go through " << s << " to " << t << ". flow=" << flow;
		return;
	}
	cout << endl << "The following edges have scheduled flow as indicated:";
	for(int i=0; i<Gup.size(); i++){ // O(V)
		int src, dst, wei, cap;
		src = i;
		for(auto pr : Gup[src]){ // O(E)
			dst = pr.first;
			cap = pr.second;
			for(auto itr=G[src].begin(); itr!=G[src].end(); itr++){ 
				// Sigma(1 to V)[e1_i*e2_i] = O(E^2)
				if(itr->first == dst){
					wei = itr->second;
					if(wei < 0)
						cout << endl << "Negative edge found when printing result. src=" << src << ", dst=" << dst << ", wei=" << wei;						
					break;
				}
			}
		
		if(cap+wei < 0){
			cout << endl << "Capacity is greater than limit: " << -cap << " > " << wei;
			break;
		} else if (-cap == wei) continue; // All reverse edges are not selected
		cout << endl << "The scheduled flow on edge (" << src << ", " << dst;
		cout << ") = " << wei+cap << " out of capacity = " << wei;		
		}	
	}
}//Graph, Table, source, sink

int BFS(vector<list<pair<int, int>>>& Gcom, vector<list<pair<int, int>>>& Gup, vector<tuple<int, bool>>& T, int s, int t){
	queue<int> Q;
	// Initialize
	int Nodes = T.size();
	{
		int src, dst;
		for(int i=0; i<Nodes; i++){
			get<0>(T[i]) = -1;
			get<1>(T[i]) = false;
		}
	}
	Q.push(s);
	// Connecting
	while(!Q.empty()){
		int src = Q.front();
		Q.pop();
		if(get<1>(T[src]) == true) continue; // ignore visited node
		get<1>(T[src]) = true;
		// vector<int> neib;
		for(auto pr: Gcom[src]){
			int dst, cap, wei;
			dst = pr.first;
			wei = pr.second;
			if(wei > 0){
				auto itr = Gup[src].begin();
				for(; itr!=Gup[src].end(); itr++){
					if(itr->first == dst) break;
				}
				cap = itr->second;
				if(cap == 0) continue;
				else if(cap > 0){
					cout << endl << "Out of bound in forward direction from " << src << " to " << dst << ". cap>0=" << cap;
				}
				if(get<1>(T[dst]) == true) continue; // do not push visited node
				get<0>(T[dst]) = src;
				Q.push(dst);
				// neib.push_back(dst);
			} else if(wei < 0){
				auto itr = Gup[dst].begin();
				for(; itr!=Gup[dst].end(); itr++){
					if(itr->first == src) break;
				}
				cap = itr->second;
				if(cap == wei) continue;
				else if(cap < wei){
					cout << endl << "Out of bound in backward direction from " << src << " to " << dst << ". cap<" << wei << "=" << cap;
				}
				if(get<1>(T[dst]) == true) continue; // do not push visited node				
				get<0>(T[dst]) = src;
				Q.push(dst);
				// neib.push_back(dst);
			}	else{ // wei == 0
				cout << endl << "Dummy edge in graph from " << src << " to " << dst;
			}
		}

		// // print neib
		// cout << endl << src << ": ";
		// for(auto e : neib) cout << e << " ";
		// cout << "|| ";

		// // sort neighbors  O(E^2)
		// for(int i=0; i<neib.size(); i++){
		// 	for(int j=i; j<neib.size(); j++){
		// 		if(neib[i] > neib[j]) swap(neib[i], neib[j]);
		// 	}
		// 	// cout << neib[i] << " ";
		// 	Q.push(neib[i]);
		// }
	}
	if(get<0>(T[t]) == -1) return 0;

	int stream = INT_MAX;
	int node = t;
	while(node != s){ // O(V)
		int from, cap, wei;
		from = get<0>(T[node]);
		wei = cap = INT_MAX;			
		for(auto itr=Gcom[from].begin(); itr!=Gcom[from].end(); itr++){ // O(E)
			if(itr->first == node){
				wei = itr->second;
				break;
			}
		}			
		for(auto itr=Gup[from].begin(); itr!=Gup[from].end(); itr++){ // O(E)
			if(itr->first == node){
				cap = itr->second;
				if(-cap < stream)
					stream = -cap;
				break;
			} 
		}
		for(auto itr=Gup[node].begin(); itr!=Gup[node].end(); itr++){ // O(E)
			if(itr->first == from){
				cap = itr->second;
				// from to node, neg wei, neg cap, stream = -wei -(-cap)
				if(cap-wei < 0);
				else if(cap-wei < stream)
					stream = cap-wei;
				break;
			}
		}
		if(stream < 0){
			cout << endl << "Stream is negative, stream=" << stream << " when src=" << from << " dst=" << node;
			return 0;
		}
		node = from;
	}
	if(stream == INT_MAX){
		cout << endl << "Failed to find a valid stream";
		return 0;
	}
	return stream;
}