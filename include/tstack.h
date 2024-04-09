// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private: 
	T* stackarr;
	int index;
public: 
	TStack() : index(-1) {
		stackarr = new T[size];
	}
	void pop() {
		if (index >= 0)
			index--;
	}
	void push(T item) {
		if (index < size - 1)
			stackarr[++index] = item;
	}
	T get() const {
		return stackarr[index];
	}
	bool isEmpty() const {
		return index == -1;
	}
};

#endif  // INCLUDE_TSTACK_H_
