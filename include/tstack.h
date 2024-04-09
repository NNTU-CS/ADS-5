// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
private:
   T* stackarr;
   int headIndex;
public:
	TStack() : headIndex(-1) {
		stackarr = new T[size];
	}
	void pop() {
		if (isEmpty())
			trow std::string("Empty");
		else
			stackarr[headIndex--];
	}
	void push(T item) {
		if (!isFull())
			stackarr[++headIndex] = item;
		else
			trow std::string("Full");
	}
	T get() const {
		return stackarr[headIndex];
	}
	bool isEmpty() const {
		return headIndex == -1;
	}
	bool isFull() const {
		return headIndex == size - 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
