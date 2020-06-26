#include "MazeInterface.h"
#include <sstream>
using namespace std;

enum CellValue { OPEN, BLOCKED, VISITED, PATH, EXIT, MLEFT, MRIGHT, MUP, MDOWN, MOUT , MIN };

class Maze : public MazeInterface{
	private: 
		int height = 0;
		int width = 0;
		int layer = 0;
		int value = 0;
		int*** maze;
		

	public: 
		//CONSTRUCTOR FOR THE ARRAY
		Maze(int newHeight, int newWidth,	int newLayer) {
			height = newHeight;
			width = newWidth;
			layer = newLayer;
			maze = new int** [width];
			for (int i = 0; i < width; ++i) {
				maze[i] = new int* [height];
				for (int k = 0; k < height; k++) {
					maze[i][k] = new int[layer];
				}

			}
		}
		//DESTRUCTOR
		~Maze(void) {
			for (int i = 0; i < width; ++i) {
				for (int k = 0; k < height; k++) {
					delete[] maze[i][k];
				}
				delete[] maze[i];
			}
			delete[] maze;
		}

		void setValue(int height, int width, int layer, int value) {	
			maze[width][height][layer] = value;
		}

		#define UP       r,c-1,l
		#define DOWN    r,c+1,l
		#define LEFT    r-1,c,l
		#define RIGHT    r+1,c,l
		#define IN		r, c, l + 1
		#define OUT		r, c, l - 1

		//RECURSION
		bool find_path(int r, int c, int l) {
			if (r < 0 || r >= width) return false;
			if (c < 0 || c >= height) return false;
			if (l < 0 || l >= layer) return false;
			if (maze[r][c][l] != OPEN) return false;

			if (r == (width - 1) && (c == (height - 1)) && (l == (layer - 1))) {
				maze[r][c][l] = EXIT;
				return true;
			}

			maze[r][c][l] = PATH;

			if (find_path(LEFT)) {
				maze[r][c][l] = MLEFT;
				return true;
			}
			else if (find_path(RIGHT)) {
				maze[r][c][l] = MRIGHT;
				return true;
			}
			else if (find_path(UP)) {
				maze[r][c][l] = MUP;
				return true;
			}
			else if (find_path(DOWN)) {
				maze[r][c][l] = MDOWN;
				return true;
			}
			else if (find_path(OUT)) {
				maze[r][c][l] = MOUT;
				return true;
			}
			else if (find_path(IN)) {
				maze[r][c][l] = MIN;
				return true;
			}

			maze[r][c][l] = VISITED;
			return false;

		}

		bool find_maze_path() {
			return find_path(0, 0, 0);
		}

		string toString() const {
			ostringstream os;
			string path = "_X_2ELRUDOI";
			for (int r = 0; r < layer; ++r){
				os << "Layer " << r + 1 << endl;
				for (int c = 0; c < height; ++c){
					for (int l = 0; l < width; l++) {
						os << " " << path[maze[l][c][r]];
					}
					os << endl;
				}
				os << endl;
			}
			return os.str();
		}
};

