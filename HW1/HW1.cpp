#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <bitset>
#include <filesystem>

using namespace std;

class Cell;
class Maze;

class Cell {
	public:
		int id;
		int wall; // S-W-N-E
		bool visited;
		Cell* from;

		Cell(const int id, const int wall);
		~Cell(){ delete from;}
		Cell* neighbor(Maze& maze); // return unvisited neighbor
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
		void print_path(ostream& out);
		void print_solution(ostream& out);
};

void MY_DFS_iterative(Maze& maze, ostream& out);
void MY_DFS_recursive(Maze& maze, Cell* cell);
void MY_DFS_recursive_wrap(Maze& maze, ostream& out);
void MY_BFS(Maze& maze, ostream& out);
void DFS_iterative(vector<Cell>& maze, int numC, int start, int end);
void DFS_recursive(vector<Cell>& maze, int numC, int start, int end, bool done);
void BFS(vector<Cell>& maze, int numC, int start, int end);

int main() {
	ifstream In("maze.txt");//the file maze.txt in in same folder as the C++ source file.
	int numR, numC;//number of rows, number of columns
	In >> numR >> numC;
	int Start, End;//beginning cell and target cell
	In >> Start >> End;

	if(numR<0 || numC<0) {
		cout << "Input error: numR=" << numR << ", numC=" << numC << endl;
		// std::filesystem::path cwd = std::filesystem::current_path();
		// cout << "Current working directory is: " << cwd.string() << endl;
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
	MY_DFS_recursive_wrap(*maze, Out);
	MY_BFS(*maze, Out);
	Out.close();
	delete maze;
	return 0;
}

void MY_DFS_iterative(Maze& maze, ostream& out){
	stack<Cell*> S;
	maze.reset();
	Cell* robot = maze.begin;
	maze.begin = maze.begin->from;
	S.push(robot);
	while(!S.empty() || !(maze.end->visited)) {
		robot = S.top();
		maze.path.push_back(robot);
		S.pop();
		if(!(robot->visited)){
			robot->visited = true;
			Cell* nb = robot->neighbor(maze);
			while(!nb && !(nb->from)){ // connect unconnected node
				nb->from = robot;
				S.push(nb);
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
void MY_DFS_recursive_wrap(Maze& maze, ostream& out){
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
	while(!(cell->neighbor(maze))){
		cell->neighbor(maze)->from = cell;
		cell = cell->neighbor(maze);
		MY_DFS_recursive(maze, cell);
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
	while(!Q.empty() || !(maze.end->visited)) {
		robot = Q.front();
		maze.path.push_back(robot);
		Q.pop();
		if(!(robot->visited)){
			robot->visited = true;
			Cell* nb = robot->neighbor(maze);
			while(!nb && !(nb->from)){
				nb->from = robot;
				Q.push(nb);
			}
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
	for(auto pr : mazemap){
		delete pr.second;
		mazemap.erase(pr.first);
	}
	mazemap.clear();
}
void Maze::reset(){
	path.clear();
	solution.clear();
}
void Maze::print_path(ostream& out){
	auto itr = path.begin();
	out << (*itr)->id;
	itr++;
	while(itr != path.end()){
		out << "->" << (*itr)->id;
		itr++;
	}
}
void Maze::print_solution(ostream& out){
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
Cell* Cell::neighbor(Maze& maze){ 
	int markDec = wall;
	string markBin = bitset<4>(markDec).to_string();
	Cell* neighbor = nullptr;
	for(int i=0; i<4; i++){
		if(markBin[1] == '1'){ // S
			neighbor = maze.mazemap.find(id+maze.cols)->second;
		} else if(markBin[0] == '1'){ // W
			neighbor = maze.mazemap.find(id-1)->second;
		} else if(markBin[3] == '1'){ // N
			neighbor = maze.mazemap.find(id-maze.cols)->second;
		} else if(markBin[2] == '1'){ // E
			neighbor = maze.mazemap.find(id+1)->second;
		}
		if(neighbor && !(neighbor->visited)) break;
		else neighbor = nullptr;
	}
	return neighbor;
}

/*
the file maze.txt contains the following:

4 5
0
19
13 11 10 10 12 5 9 10 10 4 5 5 11 10 4 3 2 10 10 6

*/