// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
	T data[size];
	int top;
public:
	TStack() : top(0) {}
	void push(const T& item) {
		if (top <= size - 1)
			data[top++] = item;
	}
	T pop() {
		if (top > 0)
			return data[--top];
	}
	bool isEmpty() {
		return top == 0;
	}
	T get() {
		if (!isEmpty())
			return data[top - 1];
	}
};

#endif  // INCLUDE_TSTACK_H_
