// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  T storage[size] = { 100 };
  int topIndex;

 public:
  TStack() : topIndex(-1) {}
  bool isFull() const {
      return topIndex >= size - 1;
  }
  void push(const T& value) {
    if (isFull()) {
      throw std::runtime_error("Cannot push: stack is full");
    }
    storage[++topIndex] = value;
  }
  bool isEmpty() const {
    return topIndex < 0;
  }

  void pop() {
    if (isEmpty()) {
      throw std::runtime_error("Cannot pop: stack is empty");
    }
    --topIndex;
  }
  const T& top() const {
    if (isEmpty()) {
      throw std::runtime_error("Cannot access top: stack is empty");
    }
    return storage[topIndex];
  }
};

#endif  // INCLUDE_TSTACK_H_
