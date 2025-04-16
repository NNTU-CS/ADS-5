// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
private:
  T elements[size];
  int currentIndex;

public:
  TStack() : currentIndex(-1) {}
  bool empty() const {
    return currentIndex < 0;
  }
  bool full() const {
    return currentIndex >= size - 1;
  }
  void push(const T& value) {
    if (full()) {
      throw std::runtime_error("Error: Stack overflow");
    }
    elements[++currentIndex] = value;
  }
  void pop() {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    --currentIndex;
  }
  T& top() {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    return elements[currentIndex];
  }
  const T& top() const {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    return elements[currentIndex];
  }
};
#endif  // INCLUDE_TSTACK_H_
