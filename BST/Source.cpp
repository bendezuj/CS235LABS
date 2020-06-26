#include <sstream>
#include <fstream>
#include <iostream>
#include "BST.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	BST<int> numbers;
	BST<string> words;

	ifstream in(argv[1]);
	ofstream out(argv[2]);
	out << argv[1] << endl;
	out << argv[2] << endl;

	for (string line; getline(in, line);) {
		string command, item;
		int integer = 0;
		if (line.size() == 0) continue;
		out << line << " ";
		istringstream iss(line);
		iss >> item;
		if (item == "STRING") {
			out << "true" << endl;
			break;
		}
		if (item == "INT") {
			out << "true " << endl;
		}
		else if (item == "add") {
			iss >> integer;
			if (numbers.addNode(integer)) {
				out << "true " << endl;
			}
			else out << "false " << endl;
		}
		else if (item == "remove") {
			iss >> integer;
			if (numbers.removeNode(integer)) {
				out << "true " << endl;
			}
			else out << "false " << endl;
		}
		else if (item == "clear") {
			if (numbers.deleteTree() == true) {
				out << "true" << endl;
			}
		}
		else if (item == "size") {
			out << numbers.getSize() << endl;
		}
		else if (item == "print") {

			out << ": " << numbers.toString() << endl;
		}
		else if (item == "find") {
			iss >> integer;
			out << numbers.findNode(integer) << endl;
		}
		else if (item == "tree") {
			out << ": ";
			if (numbers.getSize() == 0) {
				out << "empty" << endl;
			}
			else out << "" << endl;
		}
	}
	for (string line; getline(in, line);) {
		string command, item;
		int integer = 0;
		if (line.size() == 0) continue;
		out << line << " ";
		istringstream iss(line);
		iss >> item;

		if (item == "add") {
			iss >> command;
			if (words.addNode(command)) {
				out << "true " << endl;
			}
			else out << "false " << endl;
		}
		else if (item == "remove") {
			iss >> command;
			if (words.removeNode(command)) {
				out << "true " << endl;
			}
			else out << "false " << endl;
		}
		else if (item == "clear") {
			if (words.deleteTree() == true) {
				out << "true" << endl;
			}
		}
		else if (item == "size") {
			out << words.getSize() << endl;
		}
		else if (item == "print") {
			out << ": " << words.toString() << endl;
		}
		else if (item == "find") {
			iss >> command;
			out << words.findNode(command) << endl;
		}
		else if (item == "tree") {
			out << ": ";
			if (words.getSize() == 0) {
				out << "empty" << endl;
			}
			else out << "" << endl;
		}



	}
	return 0;
} 