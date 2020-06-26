#include "DequeInterface.h"
#ifndef DEQUE_H
#define DEQUE_H
using namespace std;
template<typename T>

class Deque: public DequeInterface <T> {
private:
	size_t capacity;
	size_t num_items;
	size_t front_index;
	size_t rear_index;
	T* the_data;

public:

	Deque(void) :
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(0),
		rear_index(DEFAULT_CAPACITY - 1),
		the_data(new T[DEFAULT_CAPACITY])
	{}
	~Deque(void) { delete[] the_data; }

	/** Insert item at front of deque */
	void reallocate() {
		T* newData = new T[2 * capacity];
		for (int i = 0; i < num_items; i++) {
			newData[i] = the_data[(front_index + i + capacity) % capacity];
		}
		delete[] the_data;
		the_data = newData;
		front_index = 0;
		rear_index = capacity - 1;
		capacity = 2 * capacity;

	}

	void push_front(const T& value) {
		if (num_items == capacity) {
			reallocate();
		}
		front_index = (front_index - 1 + capacity) % capacity;
		the_data[front_index] = value;
		++num_items;
		

	}

	/** Insert item at rear of deque */
	void push_back(const T& value) {
		if (num_items == capacity) {
			reallocate();
		}

		rear_index = (rear_index + 1 + capacity) % capacity;
		the_data[rear_index] = value;
		++num_items;
	}

	/** Remove the front item of the deque */
	void pop_front(void) {
		--num_items;
		front_index = (front_index + 1 + capacity) % capacity;
	}

	/** Remove the rear item of the deque */
	void pop_back(void) {
		--num_items;
		rear_index = (rear_index - 1 + capacity) % capacity;
	}

	/** Return the front item of the deque (Do not remove) */
	T& front(void) {
		return the_data[front_index];
	}

	/** Return the rear item of the deque (Do not remove) */
	T& back(void) {
		return the_data[rear_index];
	}

	/** Return the number of items in the deque */
	size_t size(void) const{
		return num_items;
	}

	/** Return true if deque is empty */
	bool empty(void) const{
		if (num_items == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	/** Return item in deque at index (0 based) */
	T& at(size_t index) {
		return the_data[(index + front_index + capacity) % capacity];
	}

	/** Return the deque items */
	string toString(void) const {
		stringstream s;
		for (int i = 0; i < num_items; i++) {
			s << the_data[(front_index + i + capacity) % capacity] << " ";
		}
		return s.str();
	}
};
#endif //DEQUE_H