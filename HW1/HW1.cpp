#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <bitset>
// #include <filesystem>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE MAX_PATH

using namespace std;

class Cell;
class Maze;
void MY_DFS_iterative(Maze& maze, ofstream& out);
void MY_DFS_recursive(Maze& maze, Cell* cell);
void MY_DFS_recursive_wrap(Maze& maze, ofstream& out);
void MY_BFS(Maze& maze, ofstream& out);
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end);
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool done);
void BFS(vector<Cell>& maze, int numC, int start, int end);

class Cell {
	public:
		int id;
		int wall; // S-W-N-E
		bool visited;
		Cell* from;

		Cell();
		Cell(const int id, const int wall);
		~Cell(){ delete from;}
		vector<Cell*> neighbor(Maze& maze); // return unvisited neighbor
		friend ostream& operator<<(ostream& str, const Cell* C);
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
		void print_path(ofstream& out);
		void print_solution(ofstream& out);
};

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
	}
	In.close();

	Maze* maze = new Maze();
	maze->rows = numR;
	maze->cols = numC;
	for(int i=0; i < numR*numC; i++){
		Cell* cell = new Cell(i, CellWalls[i]);
		maze->mazemap.insert({i, cell});
	}
	maze->begin = maze->mazemap.find(Start)->second;
	maze->end = maze->mazemap.find(End)->second;

	//Printing to file solution.txt, which will be in the same folder as maze.txt
	ofstream Out("solution.txt");
	DFS_iterative(mazeGiven, numC, Start, End);
	DFS_recursive(mazeGiven, numC, Start, End, false);
	BFS(mazeGiven, numC, Start, End);
	MY_DFS_iterative(*maze, Out);
	// MY_DFS_recursive_wrap(*maze, Out);
	// MY_BFS(*maze, Out);
	delete maze;
	Out.close();
	return 0;
}

void MY_DFS_iterative(Maze& maze, ofstream& out){
	stack<Cell*> S;
	maze.reset();
	Cell* robot = maze.begin;
	maze.begin = maze.begin->from;
	S.push(robot);
	while(!S.empty() && !(maze.end->visited)) {
		robot = S.top();
		maze.path.push_back(robot);
		S.pop();
		if(!(robot->visited)){
			robot->visited = true;
			for(auto node : robot->neighbor(maze)){
				if(node->from) continue;
				node->from = robot;
				S.push(node);
			}
		}
	}
	// cout = out;
	out << "DFS_iterative Solutions:" << endl;
	maze.print_solution(out);
	cout << "Path length is " << maze.path.size() << endl;
}
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end){

}
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool done){

}
void MY_DFS_recursive_wrap(Maze& maze, ofstream& out){
	maze.reset();
	maze.begin->from = maze.begin;
	out << "All Moves Using DFS_recursive:" << endl;
	MY_DFS_recursive(maze, maze.begin);
	out << "DFS_recursive Solutions:" << endl;
	maze.print_solution(out);
}
void MY_DFS_recursive(Maze& maze, Cell* cell){
	cell->visited = true;
	maze.path.push_back(cell);
	// while(!(cell->neighbor(maze))){
	// 	cell->neighbor(maze)->from = cell;
	// 	cell = cell->neighbor(maze);
	// 	MY_DFS_recursive(maze, cell);
	// }

}
void BFS(vector<Cell>& maze, int numC, int start, int end){

}
void MY_BFS(Maze& maze, ofstream& out){
	queue<Cell*> Q;
	maze.reset();
	Cell* robot = maze.begin;
	maze.begin->from = maze.begin;
	Q.push(robot);
	while(!Q.empty() || !(maze.end->visited)) {
		robot = Q.front();
		maze.path.push_back(robot);
		Q.pop();
		if(!(robot->visited)){
			robot->visited = true;
			// Cell* nb = robot->neighbor(maze);
			// while(!nb && !(nb->from)){
			// 	nb->from = robot;
			// 	Q.push(nb);
			// }
		}
	}
	// cout = out;
	out << "BFS Solutions:" << endl;
	maze.print_solution(out);
	cout << "Path length is " << maze.path.size() << endl;
}
Maze::Maze(){
	begin = nullptr;
	end = nullptr;
	rows = cols = 0;
}
Maze::~Maze(){
	reset();
	delete begin;
	delete end;
	auto itr = mazemap.begin();
	while(itr != mazemap.end()){
		delete itr->second;
		mazemap.erase(itr->first);
		itr++;
	}
	mazemap.clear();
}
void Maze::reset(){
	path.clear();
	solution.clear();
}
bool Maze::boundary(const int id){
	bool in;
	if(id >= 0 && id < rows*cols)
		in = true;
	else in = false;
	return in;
}
void Maze::print_path(ofstream& out){
	auto itr = path.begin();
	out << (*itr)->id;
	itr++;
	while(itr != path.end()){
		out << "->" << (*itr)->id;
		itr++;
	}
}
void Maze::print_solution(ofstream& out){
	Cell* robot;
	if(!(end->visited))
		out << "No solution." << endl;
	else{
		robot = end;
		while(robot != begin){
			solution.push_back(robot);
			out << robot->id << "<-";
			robot = robot->from;
		}
		solution.push_back(robot);
		out << robot->id << endl;
	}
}
Cell::Cell(){
	// this = nullptr;
	this->id = -1;
	this->wall = -1;
	this->from = nullptr;
	this->visited = false;
}
Cell::Cell(const int id, const int wall){
	this->id = id;
	this->wall = wall;
	this->from = nullptr;
	this->visited = false;
}
// For a square maze, 0-id cell is located in the most top-left,
// Cells are in row-major order,
// S-W-N-E = 2184, MSB-LSB 1101(2) = 7(10) 1 indicates wall, 0 for connection. 
// S-W-N-E is the sequence to visit next neighbor as well
vector<Cell*> Cell::neighbor(Maze& maze){ 
	int markDec = wall;
	string markBin = bitset<4>(markDec).to_string();
	vector<Cell*> neighbor;
	Cell *S, *W, *N, *E;
	S = W = N = E = nullptr;
	if(maze.boundary(id+maze.cols))
		S = maze.mazemap.find(id+maze.cols)->second;
	if(maze.boundary(id-1))
		W = maze.mazemap.find(id-1)->second;
	if(maze.boundary(id-maze.cols))
		N = maze.mazemap.find(id-maze.cols)->second;
	if(maze.boundary(id+1))
		E = maze.mazemap.find(id+1)->second;

	if(markBin[1] == '0' && S){ // S
		neighbor.push_back(S);
	} if(markBin[0] == '0' && W){ // W
		neighbor.push_back(W);
	} if(markBin[3] == '0' && N){ // N
		neighbor.push_back(N);
	} if(markBin[2] == '0' && E){ // E
		neighbor.push_back(E);
	}
	
	for(auto node : {S, W, N, E}){
		cout << node;
	}
	cout << endl;
	return neighbor;
}
ostream& operator<<(ostream& str, const Cell* C){
	if(!C) str << "nullptr; ";
	else
		str << "id="<< C->id << ", visited=" << C->visited << "; ";
	return str;
}
/*
the file maze.txt contains the following:

4 5
0
19
13 11 10 10 12 5 9 10 10 4 5 5 11 10 4 3 2 10 10 6

*/