// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
  T data[size];
  int top;

public:
  TStack() : top(-1) {}

  T get() const {
    return data[top];
  }

  bool isEmpty() const {
    return top == -1;
  }
  bool isFull() const {
    return top == size - 1;
  }

  void pop() {
    if (top >= 0) top--;
  }
  void push(T val) {
    if (top < size - 1) data[++top] = val;
  }
};

#endif  // INCLUDE_TSTACK_H_
