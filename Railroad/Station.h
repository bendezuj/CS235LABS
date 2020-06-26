#include "Stack.h"
#include "Queue.h"
#include "Vector.h"
template<typename T>
class Station {
private:


	Vector<T> train;
	Stack<T> stack;
	Queue<T> queue;
	T turnTableCar;
	bool empty = true;

public: 
	Station() {}
	~Station() {}
	string addCar(const T& car) {
		if (!empty) {
			return "Turntable occupied!";
		}
		else {
			turnTableCar = car;
			empty = false;
			return "OK";
		}
	}
	string removeCar() {
		if (empty) {
			return "Turntable empty!";
		}
		else {
			train.push_back(turnTableCar);
			empty = true;
			return "OK";
		}
	}
	string topCar() {
		if (empty) {
			return "Turntable empty!";
		}
		else {
			stringstream s;
			s << turnTableCar;
			return s.str();
		}
	} 
	string addStack() {
		if (empty) {
			return "Turntable empty!";
		}
		else {
			stack.push(turnTableCar);
			empty = true;
			return "OK";
		}
	}
	
	string removeStack() {
		if (!empty) {
			return "Turntable occupied!";
		}
		else if (stack.size() == 0) {
			return "Stack empty!";
		}
		else{
			turnTableCar = stack.top();
			stack.pop();
			empty = false;
			return "OK";
		}
	}

	string topStack() {
		if (stack.size() == 0) {
			return "Stack empty!";
		}
		else {
			return stack.top();
		}
	}
	string sizeStack() {
		if (stack.size() == 0) {
			return "0";
		}
		else {
			return to_string(stack.size());
		}
	}

	string addQueue() {
		if (empty) {
			return "Turntable empty!";
		}
		else {
			queue.push(turnTableCar);
			empty = true;
			return "OK";
		}
	}
	string removeQueue() {
		if (!empty) {
			return "Turntable occupied!";
		}
		else if (queue.size() == 0) {
			return "Queue empty!";
		}
		else {
			turnTableCar = queue.top();
			queue.pop();
			empty = false;
			return "OK";
		}
	}
	string topQueue() {
		if (queue.size() == 0) {
			return "Queue empty!";
		}
		else {
			return queue.top();
		}
	}
	string sizeQueue() {
		if (queue.size() == 0) {
			return "0";
		}
		else {
			return to_string(queue.size());
		}
	}
	string find(T value) {
		stringstream s;
		if (value == turnTableCar) {
			return " Turntable";
		}
		for (int i = 0; i < stack.size(); i++) {
			if (value == stack.at(i)) {
				s << " Stack[" << i << "]";
				return  s.str();
			}
		}
		for (int i = 0; i < train.size(); i++) {
			if (value == train.at(i)) {
				s << "Train[" << i << "]";
				return  s.str();
			}
		}
		for (int i = 0; i < queue.size(); i++) {
			if (value == queue.at(i)) {
				s << "Queue[" << i << "]";
				return  s.str();
			}
		}
		return "Not Found!";
	}
	const string toString() { 
		return train.toString();
	}
};

