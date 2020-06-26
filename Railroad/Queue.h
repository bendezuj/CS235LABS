#include "Deque.h"
template<typename T>
class Queue{
private:
	Deque<T> container;

public:
	Queue() {}
	~Queue() {}
	void push(const T& value) {
		container.push_back(value);
	}
	void pop() {
		container.pop_front();
	}
	T& top() {
		return container.front();
	}
	size_t size() {
		return container.size();
	}
	T& at(size_t value) {
		return container.at(value);
	}
	string toString() const {
		return container.toString();
	}



};

