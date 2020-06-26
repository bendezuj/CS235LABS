#ifndef QUICK_SORT
#define QUICK_SORT
#include "QSInterface.h"
#include <sstream>
using namespace std;
template<typename T>


class QuickSort : public QSInterface<T>{
private:
	size_t capacity_;
	size_t numItems;
	//size_t index;
	T* myArray;

public:
	QuickSort() {
		capacity_ = 0;
		numItems = 0;
		myArray = NULL;
	}
	~QuickSort() {
		if (myArray != NULL) {
			delete[] myArray;
			myArray = NULL;
		}
	}
	//Change the size of the array when necessary
	void reallocate() {
		T* newData = new T[(2 * capacity_)];
		for (int i = 0; i < numItems; i++) {
			newData[i] = myArray[i];
		}
		delete[] myArray;
		myArray = newData;
		capacity_ = 2 * capacity_;
	}

	/** Dynamically allocate an initial array to the QuickSort class. */
	bool createArray(size_t capacity) {
		if (myArray != NULL) {
			delete[] myArray;
		}
		capacity_ = capacity;
		myArray = new T[capacity_];
		numItems = 0;
		return true;
	}

	/** Add an element to the QuickSort array. Dynamically grow array as needed. */
	bool addElement(T element) {
		if (numItems == capacity_) {
			reallocate();
		}
		myArray[numItems] = element;
		++numItems;
		return true;
	}

	/** Sort the elements of a QuickSort subarray using median and partition functions. */
	bool sort(size_t left, size_t right) {
		size_t index = medianOfThree(left, right);
		if (index == -1) return false;
		size_t index2 = partition(left, right, index);
		if (index2 == -1) return false;
		sort(left, index2);
		sort(index2, right);
		return true;
	}

	/** Sort all elements of the QuickSort array using median and partition functions. */
	bool sortAll() {
		return sort(0, numItems);
	}

	/** Removes all items from the QuickSort array. */
	bool clear() {
		numItems = 0;
		return true;
	}

	/** Return size of the QuickSort array. */
	size_t capacity() const {
		return capacity_;
	}

	/** Return number of elements in the QuickSort array. */
	size_t size() const {
		return numItems;
	}

	int medianOfThree(size_t left, size_t right) {
		if (myArray == NULL || numItems == 0 || left >= right || right > numItems || left < 0) return -1;
		int d = (left + right) / 2;
		int a = myArray[left];
		int b = myArray[d];
		int c = myArray[right - 1];
		if (a > c)
			swap(a, c);
		if (b > c)
			swap(b, c);
		//Now the smallest element is the 1st one. Just check the 2nd and 3rd
		if (a > b)
			swap(a, b);
		myArray[left] = a;
		myArray[d]= b;
		myArray[right - 1] = c;
		return d;
	}

	int partition(size_t left, size_t right, size_t pivotIndex) {
		if (myArray == NULL || numItems == 0 || left >= right - 1 || right - 1 > numItems || left < 0 || pivotIndex > right - 1 || pivotIndex < left) {
			return -1;
		}
		swap(myArray[left], myArray[pivotIndex]);
		size_t up = left + 1;
		size_t down = right - 1;
		do {
			while (myArray[up] <= myArray[left] && up != right - 1 ) {
				++up;
			}
			while (myArray[down] > myArray[left] && down != left) {
				down--;
			}
			if (up < down) {
				swap(myArray[up], myArray[down]);
			}

		} while (up < down);
		swap(myArray[left], myArray[down]);
		return down;
	}

	/** @return: comma delimited string representation of the array. */
	string toString() const {
		stringstream s;
		for (int i = 0; i < numItems; i++) {
			s << myArray[i] << ",";
		}
		string stream = s.str();
		stream.pop_back();
		return stream;
	}
};
#endif

