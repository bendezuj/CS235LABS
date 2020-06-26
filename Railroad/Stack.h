#include "Deque.h"
template<typename T>

class Stack{
private :
	Deque<T> container;
		
public:
	Stack() {}
	~Stack() {}
	void push(const T& value) {
		container.push_back(value);
	}
	void pop() {
		container.pop_back();
	}
	T& top() {
		return container.back();
	}
	size_t size() {
		return container.size();
	}
	T& at(size_t value) {
		return container.at(value);
	}
	string toString() const{
		return container.toString();
	}



};

