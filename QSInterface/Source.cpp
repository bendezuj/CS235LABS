#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "QuickSort.h"

using namespace std;

int main(int argc, char* argv[]) {
        

        ifstream in(argv[1]);
        ofstream out(argv[2]);
        out << argv[1] << endl;
        out << argv[2] << endl;

        QuickSort<int> quicksort;

        string line;

        while (getline(in, line)) {
            if (line.size() == 0) {
                continue;
            }
            string item1;
            int item;
            istringstream iss(line);
            iss >> item1;
            out << item1 << " ";

            if (item1 == "QuickSort") {
                iss >> item;
                out << item;
                if (quicksort.createArray(item))
                    out << " OK" << endl;
                else
                    out << "Error" << endl;
            }
            else if (item1 == "AddToArray") {
               while (iss >> item) {
                    out << item;
                    quicksort.addElement(item);
                    if (!iss.eof())
                    {
                        out << ",";
                    }
               }
                out << " OK" << endl;
            }
            else if (item1 == "Capacity") {
                out << quicksort.capacity() << endl;
            }
            else if (item1 == "Clear") {
                quicksort.clear();
                out << "OK" << endl;
            }
            else if (item1 == "Size") {
                out << quicksort.size() << endl;
            }
            else if (item1 == "PrintArray") {
                if (quicksort.size() != 0) {
                    out << quicksort.toString() << endl;
                }
                else out << "Empty" << endl;
            }
            else if (item1 == "MedianOfThree") {
                int item2, item3;
                iss >> item2;
                out << item2 << ", ";
                iss >> item3;
                out << item3 << " = ";
                out << quicksort.medianOfThree(item2, item3) << endl;
            }
            else if (item1 == "Partition") {
                int item2, item3, item4;
                iss >> item2;
                iss >> item3;
                iss >> item4;
                out << item2 << "," << item3 << "," << item4 << " = " << quicksort.partition(item2, item3, item4) << endl;
            }
            else if (item1 == "Sort") {
                int item2, item3;
                iss >> item2;
                iss >> item3;
                out << item2 << "," << item3;
                if (quicksort.sort(item2, item3)) {
                    out << " OK" << endl;
                }
                else out << " Error";
            }
            else if (item1 == "SortAll") {
                if (quicksort.sortAll()) {
                    out << "OK" << endl;
                }
                else out << "Error" << endl;
            }
        }


	return 0;
}