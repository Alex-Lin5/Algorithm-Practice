//HW1

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include "assign.h"
#include <map>
#include <list>
#include <bitset>
#include <string>


using namespace std;


class cell {
public:
	int id;
	int wall;
	bool visited;
	int from;
	cell() { }

};

void DFS_iterative(vector<cell>& maze, int numC, int start, int end);

void DFS_recursive(vector<cell>& maze, int numC, int start, int end);

void BFS_iterative(vector<cell>& maze, int numC, int start, int end);


int main() {

	ifstream In("maze.txt");//the file maze.txt in in same folder as the C++ source file.

	int numR, numC;//number of rows, number of columns
	In >> numR >> numC;
	int Start, End;//beginning cell and target cell
	In >> Start >> End;

	vector<int> CellWalls(numR * numC);//CellWalls is a vector of size numR * numC .
	for (int i = 0; i < numR * numC; ++i) {
		In >> CellWalls[i];
	}
	In.close();
	cout << numR << " " << numC << endl;
	cout << Start << endl;
	cout << End << endl;
	for (auto i : CellWalls) cout << i << " ";
	cout << endl;

	vector<cell> mazeCells;
	cell nCell;
	for (int i = 0; i < numR * numC; ++i) {
		nCell.wall = CellWalls[i];
		nCell.visited = false;
		nCell.id = i;
		nCell.from = NULL;
		mazeCells.push_back(nCell);
	}

	ofstream Out("solution.txt");
	//Printing to file solution.txt
	Out << numR << " " << numC << endl;
	Out << Start << endl;
	Out << End << endl;
	for (auto i : CellWalls) Out << i << " ";
	Out.close();

	vector<cell> mazecopy = mazeCells;
	Out.open("solution.txt", std::ios_base::app);
	Out << "\n\nDFS_iterative Solution:\n";
	cout << "\nDFS_iterative Solution:\n";
	if (Start<0 || Start > numC * numR || End<0 || End > numC * numR) {
		Out << "No Solution:\n";
		cout << "No Solution:\n";
	}
	else {
		DFS_iterative(mazeCells, numC, Start, End);
	}
	Out.close();

	mazeCells = mazecopy;
	cout << "BFS Solution:\n";
	Out.open("solution.txt", std::ios_base::app);
	Out << "\n\nBFS Solution:\n";
	if (Start<0 || Start > numC * numR || End<0 || End > numC * numR) {
		Out << "No Solution:";
		cout << "No Solution:";
	}
	else {
		BFS_iterative(mazeCells, numC, Start, End);
	}
	Out.close();

	mazeCells = mazecopy;
	cout << "All Moves Using DFS_recursive:\n";
	Out.open("solution.txt", std::ios_base::app);
	Out << "\n\nAll Moves Using DFS_recursive:\n";
	if (Start<0 || Start > numC * numR || End<0 || End > numC * numR) {
		Out << "No Solution:\n";
		cout << "No Solution:\n";
		cout << "DFS_recursive\n";
		Out << "DFS_recursive:\n";
		Out << "No Solution:\n";
	}
	else {
		DFS_recursive(mazeCells, numC, Start, End);
	}
	Out.close();

}


void DFS_iterative(vector<cell>& maze, int numC, int start, int end) {
	stack<int> sVar;

	cell cellObj = maze[start];
	cellObj.from = cellObj.id;
	sVar.push(cellObj.id);

	while (!sVar.empty()) {
		int src = sVar.top();
		if (src != end) { //checking whether it reached end point or not
			sVar.pop();
			if (maze[src].visited == false) {
				maze[src].visited = true;
				vector<int> neighbours;
				int cellWalls = maze[src].wall;
				if (cellWalls <= 0) {
					cout << "No Solution For DFS iterative\n";
					ofstream log;
					log.open("solution.txt", std::ios_base::app);
					log << "No Solution For DFS iterative";
					log.close();
					break;
				}
				else {
					std::string cellWallBinary = std::bitset<4>(cellWalls).to_string(); //converting int to binary
					char north = cellWallBinary[0];
					char east = cellWallBinary[1];
					char south = cellWallBinary[2];
					char west = cellWallBinary[3];

					// getting neighbours in S-W-N-E directions
					if (south == '0') {
						neighbours.push_back(src + numC);
					}

					if (west == '0') {
						neighbours.push_back(src - 1);
					}

					if (north == '0') {
						neighbours.push_back(src - numC);
					}

					if (east == '0') {
						neighbours.push_back(src + 1);
					}

					for (int ngbr : neighbours) {
						if (!maze[ngbr].visited) {
							maze[ngbr].from = src;
							sVar.push(ngbr); //pushing neigbour into stack
						}
					}
				}

			}
		}
		else {
			cell c = maze.at(end);
			ofstream log;

			log.open("solution.txt", std::ios_base::app);
			while (c.from != c.id) {
				if (maze.at(end).wall == 15) {
					cout << "No Solution For DFS iterative\n";
					log << "No Solution For DFS iterative\n";
					break;
				}
				else {
					if (c.id == start) {
						break;
					}
					log << c.id << " <- ";
					cout << c.id << " <- "; // printing the path of maze
					c = maze.at(c.from);
				}
			}
			if (maze.at(end).wall != 15) {
				log << start << "\n";
				cout << start << "\n"; // printing start point
			}
			log.close();
			break;
		}
	}
}

void BFS_iterative(vector<cell>& maze, int numC, int start, int end) {
	queue<int> qVar;

	cell cellObj = maze[start];
	cellObj.from = cellObj.id;
	qVar.push(cellObj.id);

	while (!qVar.empty()) {
		int src = qVar.front();
		if (src != end) {
			qVar.pop();
			if (maze[src].visited == false) {
				maze[src].visited = true;
				vector<int> neighbours;
				int cellWalls = maze[src].wall;
				if (cellWalls <= 0) {
					cout << "No Solution\n";
					break;
				}
				else {
					std::string cellWallBinary = std::bitset<4>(cellWalls).to_string(); //converting int to binary
					char north = cellWallBinary[0];
					char east = cellWallBinary[1];
					char south = cellWallBinary[2];
					char west = cellWallBinary[3];

					if (east == '0') {
						neighbours.push_back(src + 1);
					}

					if (north == '0') {
						neighbours.push_back(src - numC);
					}

					if (west == '0') {
						neighbours.push_back(src - 1);
					}

					if (south == '0') {
						neighbours.push_back(src + numC);
					}

					if (neighbours.size() > 0) {
						for (int ngbr : neighbours) {
							if (!maze[ngbr].visited) {
								maze[ngbr].from = src;
								qVar.push(ngbr);
							}
						}
					}
					else {
						cout << "\n Unable to find Neighbours";
					}
				}
			}
		}
		else {
			cell c = maze.at(end);
			ofstream log;
			log.open("solution.txt", std::ios_base::app);
			while (c.from != c.id) {
				if (maze.at(end).wall == 15) {
					cout << "No Solution For BFS iterative\n";
					log << "No Solution For BFS iterative\n";
					break;
				}
				else {
					if (c.id == start) {
						break;
					}
					log << c.id << " <- ";
					cout << c.id << " <- "; // printing the path of maze
					c = maze.at(c.from);
				}
			}
			log << start << "\n";
			cout << start << "\n"; // printing start point
			log.close();
			break;
		}
	}
}


void DFS_recursive(vector<cell>& maze, int numC, int start, int end) {
	cell cellObj = maze[start];
	int src = cellObj.id;
	vector<int> allmoves;
	ofstream log;

	if (maze[src].visited == false) {
		maze[src].visited = true;
		vector<int> neighbours;
		int cellWalls = maze[src].wall;
		if (cellWalls <= 0) {
			cout << "No Solution For DFS Recursive\n";
			exit(0);
		}
		else {
			std::string cellWallBinary = std::bitset<4>(cellWalls).to_string(); //converting int to binary

			char north = cellWallBinary[0];
			char east = cellWallBinary[1];
			char south = cellWallBinary[2];
			char west = cellWallBinary[3];
			if (south == '0') {
				neighbours.push_back(src + numC);
			}

			if (west == '0') {
				neighbours.push_back(src - 1);
			}

			if (north == '0') {
				neighbours.push_back(src - numC);
			}

			if (east == '0') {
				neighbours.push_back(src + 1);
			}

			if (maze.at(src).from == maze.at(start).id) {
				cout << maze.at(src).from << " -> ";
				log.open("solution.txt", std::ios_base::app);
				log << maze.at(src).from << " -> ";
				log.close();
			}
			for (int ngbr : neighbours) {
				if (!maze[ngbr].visited && ngbr>0 && ngbr<maze.size()) {
					if (ngbr == end) {
						maze.at(end).from = src;
						maze.at(end).visited = true;
						if (maze.at(end).wall != 15) {
							cout << ngbr << "\n";
							log.open("solution.txt", std::ios_base::app);
							log << ngbr << "\n";
							log.close();
						}
						else {
							log.open("solution.txt", std::ios_base::app);
							cout << "No Solution" << " -> ";
							log << "No solution" << "\n";
							log.close();
						}
						break;
					}
					maze[ngbr].from = src;
					cout << ngbr << " -> ";
					log.open("solution.txt", std::ios_base::app);
					log << ngbr << " -> ";
					log.close();
					DFS_recursive(maze, numC, ngbr, end);
				}
			}
		}
	}
	if (maze.at(src).from == maze.at(start).id && maze.at(end).visited == true) {
		log.open("solution.txt", std::ios_base::app);
		log << "\n \nDFS Recursive Solution:\n";
		cout << "\nDFS Recursive Solution: \n";
		cell c = maze.at(end);
		if (c.wall > 0) {
			while (c.from != c.id) {
				cout << c.id << " <- ";
				log << c.id << " <- ";
				if (c.id == start) {
					break;
				}
				c = maze.at(c.from);
			}
			cout << start << endl;
			log << start << endl;
		}
		else {
			cout << "No Solution For DFS Recursive\n";
			log << "No Solution For DFS Recursive\n";
		}
		log.close();
	}
}