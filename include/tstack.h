// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  T arr[size];
  int top;
public:
  TStack() : top(-1) {}

  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == size - 1;
  }

  T get() const {
    return arr[top];
  }
  void pop() {
  	if (isempty()) {
			throw std::runtime_error("Stack is empty");
    }
    top--;
  }
  void push(const T& item) {
    if (isfull()) {
      throw std::runtime_error("Stack is full");
    }
    arr[++top] = item;
  }

};

#endif  // INCLUDE_TSTACK_H_
