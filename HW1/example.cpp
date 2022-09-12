#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
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


	//Printing to file solution.txt, which will be in the same folder as maze.txt
	ofstream Out("solution.txt");
	Out << numR << " " << numC << endl;
	Out << Start << endl;
	Out << End << endl;
	for (auto i : CellWalls) Out << i << " ";
	Out.close();

	cout << endl;
	stack<int> S;
	S.push(1);
	S.push(2);
	S.push(3);
	S.push(4);
	while (!S.empty()) {
		cout << S.top() <<" ";
		S.pop();
	}

	cout << endl;
	queue<int> Q;
	Q.push(1);
	Q.push(2);
	Q.push(3);
	Q.push(4);
	while (!Q.empty()) {
		cout << Q.front() <<" ";
		Q.pop();
	}




	return 0;
}

/*
the file maze.txt contains the following:

4 5
0
19
9 10 10 10 12 5 9 10 10 6 5 5 11 10 12 7 3 10 10 6

*/