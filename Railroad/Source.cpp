#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK;
#endif
#include <sstream>
#include <fstream>
#include <iostream>
#include "Station.h"
using namespace std;

int main(int argc, char* argv[]) {
    VS_MEM_CHECK
        // Your program...
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    out << argv[1] << endl;
    out << argv[2] << endl;
    Station<string> myStation;

    for (string line; getline(in, line);) {
        try {
            string command, item1;
            if (line.size() == 0) continue;
            out << endl << line << " ";
            istringstream iss(line);
            iss >> command;
            if (command == "Add:station") {
                iss >> item1;
                out << myStation.addCar(item1);
            }
            else if (command == "Add:queue") {
                iss >> item1;
                out << myStation.addQueue();
            }
            else if (command == "Add:stack") {
                iss >> item1;
                out << myStation.addStack();
            }
            else if (command == "Remove:station") {
                out << myStation.removeCar();
            }
            else if (command == "Remove:queue") {
                out << myStation.removeQueue();
            }
            else if (command == "Remove:stack") {
                out << myStation.removeStack();
            }
            else if (command == "Top:station") {
                out << myStation.topCar();
            }
            else if (command == "Top:queue") {
                out << myStation.topQueue();
            }
            else if (command == "Top:stack") {
                out << myStation.topStack();
            }
            else if (command == "Size:queue") {
                out << myStation.sizeQueue();
            }
            else if (command == "Size:stack") {
                out << myStation.sizeStack();
            }
            else if (command == "Train:") {
                out << myStation.toString();
            }
            else if (command == "Find:") {
                iss >> item1;
                out << myStation.find(item1);
            }
        }
        catch (string bad) {
            out << bad << endl;
        }
    }
    return 0;
}


