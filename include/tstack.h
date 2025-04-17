// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, int size>
class TStack {
 private:
  T data[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& value) {
    if (full()) throw std::overflow_error("stack overflow");
    date[++topIndex] = value;
  }

  void pop() {
    if (empty()) throw std::underflow_error("stack underflow");
    --topIndex;
  }

  T& top() {
    if (empty()) throw std::underflow_error("stack is empty");
    return date[topIndex];
  }

  const T& top() const {
    if (empty()) throw std::underflow_error("stack is empty");
    return date[topIndex];
  }

  int size() const { return topIndex + 1 };
  bool empty() const { return topIndex == -1 };
  bool full() const {return topIndex == size - 1}
};

#endif  // INCLUDE_TSTACK_H_
