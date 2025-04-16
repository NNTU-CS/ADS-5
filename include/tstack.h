// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, size_t N>
class TStack {
 private:
  T arr[N];
  int top = -1;

 public:
  TStack() = default;

  bool isEmpty() const {
    return top == -1;
  }

  void push(const T& value) {
    if (top >= static_cast<int>(N) - 1) {
      throw std::overflow_error("Stack overflow");
    }
    arr[++top] = value;
  }

  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack underflow");
    }
    --top;
  }

  T get() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return arr[top];
  }

  size_t size() const {
    return top + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
