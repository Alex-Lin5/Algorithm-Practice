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
void MY_DFS_iterative(Maze& maze, ostream& out);
void MY_DFS_recursive(Maze& maze, Cell* cell);
void MY_DFS_recursive_wrap(Maze& maze, ostream& out);
void MY_BFS(Maze& maze, ostream& out);
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
		~Cell(){ from = nullptr;}
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
		void get_solution();
		void print_path(ostream& out);
		void print_solution(ostream& out);
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
	MY_DFS_iterative(*maze, cout);
	MY_BFS(*maze, cout);
	MY_DFS_recursive_wrap(*maze, cout);
	// MY_DFS_iterative(*maze, Out);
	// MY_BFS(*maze, Out);
	// MY_DFS_recursive_wrap(*maze, Out);
	delete maze;
	Out.close();
	return 0;
}

void MY_DFS_iterative(Maze& maze, ostream& out){
	stack<Cell*> S;
	maze.reset();
	Cell* robot = maze.begin;
	maze.begin->from = maze.begin;
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
	out << endl << "DFS_iterative Solutions:" << endl;
	maze.get_solution();
	maze.print_solution(out);
	cout << "Path length is " << maze.path.size() << endl;
	maze.print_path(cout);

}
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end){

}
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool done){

}
void MY_DFS_recursive_wrap(Maze& maze, ostream& out){
	maze.reset();
	maze.begin->from = maze.begin;
	out << endl << "All Moves Using DFS_recursive:" << endl;
	MY_DFS_recursive(maze, maze.begin);
	cout << "Path length is " << maze.path.size() << endl;
	maze.print_path(out);
	out << "DFS_recursive Solutions:" << endl;
	maze.get_solution();
	maze.print_solution(out);
}
void MY_DFS_recursive(Maze& maze, Cell* cell){
	// cout << "cell: " << cell << endl;
	cell->visited = true;
	if(maze.end->visited) return;
	maze.path.push_back(cell);
	for(auto node : cell->neighbor(maze)){
		// cout << "node: " << node << endl;
		if(node->visited) continue;
		node->from = cell;
		MY_DFS_recursive(maze, node);
	}
}
void BFS(vector<Cell>& maze, int numC, int start, int end){

}
void MY_BFS(Maze& maze, ostream& out){
	queue<Cell*> Q;
	maze.reset();
	Cell* robot = maze.begin;
	maze.begin->from = maze.begin;
	Q.push(robot);
	while(!Q.empty() && !(maze.end->visited)) {
		robot = Q.front();
		maze.path.push_back(robot);
		Q.pop();
		if(!(robot->visited)){
			robot->visited = true;
			for(auto node : robot->neighbor(maze)){
				if(node->from) continue;
				node->from = robot;
				Q.push(node);
			}
		}
	}
	out << endl << "BFS Solutions:" << endl;
	maze.get_solution();
	maze.print_solution(out);
	cout << "Path length is " << maze.path.size() << endl;
	maze.print_path(cout);
}
Maze::Maze(){
	begin = nullptr;
	end = nullptr;
	rows = cols = 0;
}
Maze::~Maze(){
	cout << endl << "Delete maze: " << this << endl;
	reset();
	begin = nullptr;
	end = nullptr;
	for(auto& pr : mazemap){
		// cout << pr.second << endl;
		delete pr.second;
		// mazemap.erase(pr.first);
	}

	mazemap.clear();
}
void Maze::reset(){
	path.clear();
	solution.clear();
	for(auto pr : mazemap){
		(pr.second)->from = nullptr;
		(pr.second)->visited = false;
	}
}
bool Maze::boundary(const int id){
	bool in;
	if(id >= 0 && id < rows*cols)
		in = true;
	else in = false;
	return in;
}
void Maze::get_solution(){
	Cell* robot;
	if(!(end->visited))
		return;
	else{
		robot = end;
		while(robot != begin){
			solution.push_back(robot);
			robot = robot->from;
		}
		solution.push_back(robot);
	}
}

void Maze::print_path(ostream& out){
	auto itr = path.begin();
	out << (*itr)->id;
	itr++;
	while(itr != path.end()){
		out << "->" << (*itr)->id;
		itr++;
	}
	out << endl;
}
void Maze::print_solution(ostream& out){
	if(!(end->visited))
		out << "No solution." << endl;
	else{
		auto itr = solution.begin();
		out << (*itr)->id;
		itr++;
		while(itr != solution.end()){
			out << "<-" << (*itr)->id;
			itr++;
		}
		out << endl;
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
// S-W-N-E = 2184, MSB-LSB Index[0, 1, 2, 3] 1101(2) = 13(10) 1 indicates wall, 0 for connection. 
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

	if(markBin[2] == '0' && S){ // S
		neighbor.push_back(S);
	} if(markBin[3] == '0' && W){ // W
		neighbor.push_back(W);
	} if(markBin[0] == '0' && N){ // N
		neighbor.push_back(N);
	} if(markBin[1] == '0' && E){ // E
		neighbor.push_back(E);
	}
	// cout << "this: " << this << endl;
	// cout << "neighbor: ";
	for(auto node : neighbor){
		// cout << node;
	}
	// cout << endl << endl;
	return neighbor;
}
ostream& operator<<(ostream& str, const Cell* C){
	if(!C) str << "nullptr; ";
	else{
		str << boolalpha << "ID="<< C->id << ", Vst=" << C->visited;
		str << ", Cnt=" << ((C->from==nullptr)?false:true) << "; ";
		// str << ", wall=" << C->wall << ", from=" << C->from << "; ";
	}
	return str;
}
