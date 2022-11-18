#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <bitset>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE MAX_PATH

using namespace std;

class Cell;
class Maze;
void MY_DFS_iterative(Maze& maze, ostream& out);
void MY_DFS_recursive(Maze& maze, Cell* cell);
void MY_DFS_recursive_wrap(Maze& maze, ostream& out);
void MY_BFS(Maze& maze, ostream& out);
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end);
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool &done);
void BFS(vector<Cell>& maze, int numC, int start, int end);

class Cell {
	public:
		int id;
		int wall; // S-W-N-E
		bool visited;
		// Cell* from;
		int from;

		Cell();
		Cell(const int id, const int wall);
		// ~Cell(){ from = nullptr;}
		// vector<Cell*> neighbor(Maze& maze); // return unvisited neighbor
		// friend ostream& operator<<(ostream& str, const Cell* C);
};

class Maze {
	public:
		int rows;
		int cols;
		Cell* begin;
		Cell* end;
		map<int, Cell*> mazemap;
		vector<Cell*> path;
		vector<Cell*> solution;

		Maze();
		Maze(int row, int col);
		~Maze();
		void reset();
		bool boundary(const int id);
		void get_solution();
		void print_path(ostream& out);
		void print_solution(ostream& out);
};

ofstream Out("solution.txt");
int main() {
	TCHAR buffer[BUFSIZE];
	DWORD dwRet = GetCurrentDirectory(BUFSIZE, buffer);
	cout << "Current directory is: "<< buffer << endl;
	ifstream In("maze.txt");//the file maze.txt in in same folder as the C++ source file.
	int numR, numC;//number of rows, number of columns
	In >> numR >> numC;
	int Start, End;//beginning cell and target cell
	In >> Start >> End;

	if(numR<0 || numC<0) {
		cout << "Input error: numR=" << numR << ", numC=" << numC << endl;
		return -1;
	}

	vector<Cell> mazeGiven;
	vector<int> CellWalls(numR * numC);//CellWalls is a vector of size numR * numC .
	for (int i = 0; i < numR * numC; ++i) {
		In >> CellWalls[i];
		Cell* cell = new Cell(i, CellWalls[i]);
		mazeGiven.push_back(*cell);
		mazeGiven[i].visited = false;
		mazeGiven[i].from = -1;
	}
	In.close();

	//Printing to file solution.txt, which will be in the same folder as maze.txt
	int size = mazeGiven.size();
	Out << endl << "DFS_iterative Solutions:" << endl;
	DFS_iterative(mazeGiven, numC, Start, End);
	if(mazeGiven[End].from == -1)
		Out << "No solution." << endl;
	else{
		int now = End;
		while(now != Start){
			Out << now << "<-";
			now = mazeGiven[now].from;
		}
		Out << Start << endl << endl;
	}

	for(int i=0; i<size; i++){
		mazeGiven[i].from = -1;
		mazeGiven[i].visited = false;
	}
	Out << endl << "BFS Solutions:" << endl;
	BFS(mazeGiven, numC, Start, End);
	if(mazeGiven[End].from == -1)
		Out << "No solution." << endl;
	else{
		int now = End;
		while(now != Start){
			Out << now << "<-";
			now = mazeGiven[now].from;
		}
		Out << Start << endl << endl;
	}

	for(int i=0; i<size; i++){
		mazeGiven[i].from = -1;
		mazeGiven[i].visited = false;
	}
	Out << endl << "All Moves Using DFS_recursive:" << endl;
	mazeGiven[Start].from = Start;
	bool done = false;
	DFS_recursive(mazeGiven, numC, Start, End, done);
	Out << endl << "DFS_recursive Solutions:" << endl;
	if(mazeGiven[End].from == -1)
		Out << "No solution." << endl;
	else{
		int now = End;
		while(now != Start){
			Out << now << "<-";
			now = mazeGiven[now].from;
		}
		Out << Start << endl << endl;
	}

	// Maze* maze = new Maze();
	// maze->rows = numR;
	// maze->cols = numC;
	// for(int i=0; i < numR*numC; i++){
	// 	Cell* cell = new Cell(i, CellWalls[i]);
	// 	maze->mazemap.insert({i, cell});
	// }
	// maze->begin = maze->mazemap.find(Start)->second;
	// maze->end = maze->mazemap.find(End)->second;
	// MY_DFS_iterative(*maze, Out);
	// MY_BFS(*maze, Out);
	// MY_DFS_recursive_wrap(*maze, Out);
	// delete maze;
	Out.close();
	return 0;
}

// void MY_DFS_iterative(Maze& maze, ostream& out){
// 	stack<Cell*> S;
// 	maze.reset();
// 	Cell* robot = maze.begin;
// 	maze.begin->from = maze.begin;
// 	S.push(robot);
// 	while(!S.empty() && !(maze.end->visited)) {
// 		robot = S.top();
// 		maze.path.push_back(robot);
// 		S.pop();
// 		if(!(robot->visited)){
// 			robot->visited = true;
// 			for(auto node : robot->neighbor(maze)){
// 				if(node->from) continue;
// 				node->from = robot;
// 				S.push(node);
// 			}
// 		}
// 	}
// 	out << endl << "DFS_iterative Solutions:" << endl;
// 	maze.get_solution();
// 	maze.print_solution(out);
// 	cout << "Path length is " << maze.path.size() << endl;
// 	maze.print_path(cout);
// }
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end){
	stack<int> Stk;
	int robot = start;
	maze[start].from = start;
	Stk.push(robot);
	while(!Stk.empty() && (maze[end].from == -1)){
		robot = Stk.top();
		Stk.pop();
		Cell now = maze[robot];
		if(!now.visited){
			now.visited = true;
			vector<int> neighbor;
			int size = maze.size();
			string bin = bitset<4>(now.wall).to_string();
			if(robot+numC<size && bin[2] == '0')
				neighbor.push_back(robot+numC);
			if(robot-1>=0 && bin[3] == '0')
				neighbor.push_back(robot-1);
			if(robot-numC>=0 && bin[0] == '0')
				neighbor.push_back(robot-numC);
			if(robot+1<size && bin[1] == '0')
				neighbor.push_back(robot+1);
			for(auto node : neighbor){
				if(maze[node].from != -1) continue;
				maze[node].from = robot;
				Stk.push(node);
			}
		}
	}
}
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool &done){
	int now = start;
	if(maze[end].from != -1) done = true;
	// if(maze[start].visited) done = true;
	if(done){
		Out << end;
		return;
	} 
	Out << now << "->";
	maze[now].visited = true;

	vector<int> neighbor;
	int size = maze.size();
	string bin = bitset<4>(maze[now].wall).to_string();
	if(now+numC<size && bin[2] == '0')
		neighbor.push_back(now+numC);
	if(now-1>=0 && bin[3] == '0')
		neighbor.push_back(now-1);
	if(now-numC>=0 && bin[0] == '0')
		neighbor.push_back(now-numC);
	if(now+1<size && bin[1] == '0')
		neighbor.push_back(now+1);
	for(auto node : neighbor){
		if(done) return;
		if(maze[node].visited) continue;
		maze[node].from = start;
		DFS_recursive(maze, numC, node, end, done);
	}
}
// void MY_DFS_recursive_wrap(Maze& maze, ostream& out){
// 	maze.reset();
// 	maze.begin->from = maze.begin;
// 	out << endl << "All Moves Using DFS_recursive:" << endl;
// 	MY_DFS_recursive(maze, maze.begin);
// 	cout << "Path length is " << maze.path.size() << endl;
// 	maze.print_path(out);
// 	out << "DFS_recursive Solutions:" << endl;
// 	maze.get_solution();
// 	maze.print_solution(out);
// }
// void MY_DFS_recursive(Maze& maze, Cell* cell){
// 	// cout << "cell: " << cell << endl;
// 	cell->visited = true;
// 	if(maze.end->visited) return;
// 	maze.path.push_back(cell);
// 	for(auto node : cell->neighbor(maze)){
// 		// cout << "node: " << node << endl;
// 		if(node->visited) continue;
// 		node->from = cell;
// 		MY_DFS_recursive(maze, node);
// 	}
// }
void BFS(vector<Cell>& maze, int numC, int start, int end){
	queue<int> Q;
	int robot = start;
	maze[start].from = start;
	Q.push(robot);
	while(!Q.empty() && (maze[end].from == -1)){
		robot = Q.front();
		Q.pop();
		Cell now = maze[robot];
		if(!now.visited){
			now.visited = true;
			vector<int> neighbor;
			int size = maze.size();
			string bin = bitset<4>(now.wall).to_string();
			if(robot+numC<size && bin[2] == '0')
				neighbor.push_back(robot+numC);
			if(robot-1>=0 && bin[3] == '0')
				neighbor.push_back(robot-1);
			if(robot-numC>=0 && bin[0] == '0')
				neighbor.push_back(robot-numC);
			if(robot+1<size && bin[1] == '0')
				neighbor.push_back(robot+1);
			for(auto node : neighbor){
				if(maze[node].from != -1) continue;
				maze[node].from = robot;
				Q.push(node);
			}
		}
	}

}
// void MY_BFS(Maze& maze, ostream& out){
// 	queue<Cell*> Q;
// 	maze.reset();
// 	Cell* robot = maze.begin;
// 	maze.begin->from = maze.begin;
// 	Q.push(robot);
// 	while(!Q.empty() && !(maze.end->visited)) {
// 		robot = Q.front();
// 		maze.path.push_back(robot);
// 		Q.pop();
// 		if(!(robot->visited)){
// 			robot->visited = true;
// 			for(auto node : robot->neighbor(maze)){
// 				if(node->from) continue;
// 				node->from = robot;
// 				Q.push(node);
// 			}
// 		}
// 	}
// 	out << endl << "BFS Solutions:" << endl;
// 	maze.get_solution();
// 	maze.print_solution(out);
// 	cout << "Path length is " << maze.path.size() << endl;
// 	maze.print_path(cout);
// }
// Maze::Maze(){
// 	begin = nullptr;
// 	end = nullptr;
// 	rows = cols = 0;
// }
// Maze::~Maze(){
// 	cout << endl << "Delete maze: " << this << endl;
// 	reset();
// 	begin = nullptr;
// 	end = nullptr;
// 	for(auto& pr : mazemap){
// 		// cout << pr.second << endl;
// 		delete pr.second;
// 		// mazemap.erase(pr.first);
// 	}

// 	mazemap.clear();
// }
// void Maze::reset(){
// 	path.clear();
// 	solution.clear();
// 	for(auto pr : mazemap){
// 		(pr.second)->from = nullptr;
// 		(pr.second)->visited = false;
// 	}
// }
// bool Maze::boundary(const int id){
// 	bool in;
// 	if(id >= 0 && id < rows*cols)
// 		in = true;
// 	else in = false;
// 	return in;
// }
// void Maze::get_solution(){
// 	Cell* robot;
// 	if(!(end->visited))
// 		return;
// 	else{
// 		robot = end;
// 		while(robot != begin){
// 			solution.push_back(robot);
// 			robot = robot->from;
// 		}
// 		solution.push_back(robot);
// 	}
// }

// void Maze::print_path(ostream& out){
// 	auto itr = path.begin();
// 	out << (*itr)->id;
// 	itr++;
// 	while(itr != path.end()){
// 		out << "->" << (*itr)->id;
// 		itr++;
// 	}
// 	out << endl;
// }
// void Maze::print_solution(ostream& out){
// 	if(!(end->visited))
// 		out << "No solution." << endl;
// 	else{
// 		auto itr = solution.begin();
// 		out << (*itr)->id;
// 		itr++;
// 		while(itr != solution.end()){
// 			out << "<-" << (*itr)->id;
// 			itr++;
// 		}
// 		out << endl;
// 	}
// }
Cell::Cell(){
	this->id = -1;
	this->wall = -1;
	// this->from = nullptr;
	this->from = -1;
	this->visited = false;
}
Cell::Cell(const int id, const int wall){
	this->id = id;
	this->wall = wall;
	// this->from = nullptr;
	this->from = -1;
	this->visited = false;
}
// For a square maze, 0-id cell is located in the most top-left,
// Cells are in row-major order,
// S-W-N-E = 2184, MSB-LSB Index[0, 1, 2, 3] 1101(2) = 13(10) 1 indicates wall, 0 for connection. 
// S-W-N-E is the sequence to visit next neighbor as well
// vector<Cell*> Cell::neighbor(Maze& maze){ 
// 	int markDec = wall;
// 	string markBin = bitset<4>(markDec).to_string();
// 	vector<Cell*> neighbor;
// 	Cell *S, *W, *N, *E;
// 	S = W = N = E = nullptr;
// 	if(maze.boundary(id+maze.cols))
// 		S = maze.mazemap.find(id+maze.cols)->second;
// 	if(maze.boundary(id-1))
// 		W = maze.mazemap.find(id-1)->second;
// 	if(maze.boundary(id-maze.cols))
// 		N = maze.mazemap.find(id-maze.cols)->second;
// 	if(maze.boundary(id+1))
// 		E = maze.mazemap.find(id+1)->second;

// 	if(markBin[2] == '0' && S){ // S
// 		neighbor.push_back(S);
// 	} if(markBin[3] == '0' && W){ // W
// 		neighbor.push_back(W);
// 	} if(markBin[0] == '0' && N){ // N
// 		neighbor.push_back(N);
// 	} if(markBin[1] == '0' && E){ // E
// 		neighbor.push_back(E);
// 	}
// 	// cout << "this: " << this << endl;
// 	// cout << "neighbor: ";
// 	for(auto node : neighbor){
// 		// cout << node;
// 	}
// 	// cout << endl << endl;
// 	return neighbor;
// }
// ostream& operator<<(ostream& str, const Cell* C){
// 	if(!C) str << "nullptr; ";
// 	else{
// 		str << boolalpha << "ID="<< C->id << ", Vst=" << C->visited;
// 		str << ", Cnt=" << ((C->from==nullptr)?false:true) << "; ";
// 		// str << ", wall=" << C->wall << ", from=" << C->from << "; ";
// 	}
// 	return str;
// }
