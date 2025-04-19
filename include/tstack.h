// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  T data[size];
  int top = -1;

 public:
  void push(const T& val) {
    if (top >= size - 1)
      throw std::runtime_error("Stack overflow");
    data[++top] = val;
  }

  T pop() {
    if (top < 0)
      throw std::runtime_error("Stack underflow");
    return data[top--];
  }

  T topElem() const {
    if (top < 0)
      throw std::runtime_error("Stack is empty");
    return data[top];
  }

  bool isEmpty() const {
    return top == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
