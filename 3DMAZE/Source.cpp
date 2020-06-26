#include <sstream>
#include <fstream>
#include <iostream>
#include "Maze.h"

using namespace std;


int main(int argc, char* argv[]) {
	ifstream in(argv[1]);
	ofstream out(argv[2]);
	out << argv[1] << endl;
	out << argv[2] << endl;
	
	int height;
	int width;
	int layers;

	in >> height >> width >> layers;
	Maze myMaze = Maze(height, width, layers);

	for (int i = 0; i < layers; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++) {
				int value;
				in >> value;
				myMaze.setValue(j, k, i, value);
			}
		}
	}
	out << "Solve Maze:" << endl << myMaze.toString();
	if (myMaze.find_maze_path() == true) {
		out << "Solution:" << endl << myMaze.toString();
	}
	else {
		out << " No Solution Exists!" << endl;
	}



	return 0;
}