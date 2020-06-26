#include <sstream>
#include <fstream>
#include <iostream>
#include "ExpressionManager.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

    ifstream in(argv[1]);
    ofstream out(argv[2]);
    out << argv[1] << endl;
    out << argv[2] << endl;   
    vector<string> strings;
    ExpressionManager myExp;

    for (string line; getline(in, line);) {
        try {
            string command, item1;
            if (line.size() == 0) continue;
            out << endl << line << " ";
            istringstream iss(line);
            iss >> command;
            if (command == "Expression:") {                
                line = line.substr(12);
                myExp.setExpression(line);
                continue;
            }
            if (command == "Infix:") {
                out << myExp.infix();
                if (myExp.infix() != "Unbalanced" && myExp.infix() != "Missing Operand" && myExp.infix() != "Missing Operator") {
                    continue;
                }
                else {
                    break;
                }
            }
            if (command == "Postfix:") {
                out << myExp.postfix();
                continue;
            }
            if (command == "Prefix:") {
                out << myExp.prefix();
                continue;
            }
            if (command == "Value:") {
                out << myExp.value();
                continue;
            }

        }
        catch (string bad) {
            out << bad << endl;
        }
    }
    return 0;
}



