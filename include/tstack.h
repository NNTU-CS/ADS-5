// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>
template <typename T, int k>
class TStack {
 private:
  T data[k];
  int top;
 public:
  TStack(): top(-1) {}
  bool isEmpty() const { return top < 0;
  }
  bool isFull() const { return top >= (k - 1);
  }
  void push(const T& value) {
    if (isFull()) throw std::string("Stack is full!");
    data[++top] = value;
  }
  void pop() {
    if (isEmpty()) throw std::string("Stack is empty!");
    top--;
  }
  const T& getTop() const {
    if (isEmpty()) throw std::string("Stack is empty!");
    return data[top];
  }
};

#endif  // INCLUDE_TSTACK_H_
