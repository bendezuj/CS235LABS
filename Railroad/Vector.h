#include "Deque.h"


template<typename T>
class Vector{
	private:
		Deque<T> container;
	
	public:
		Vector() {}
		~Vector() {}
		void push_back(const T& value) {
			container.push_back(value);
		}
		void pop_back() {
			container.pop_back();
		}
		T& back() {
			return container.back();
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

