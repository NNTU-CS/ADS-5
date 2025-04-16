// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>
#include <array>

template<typename T, int kStackSize>
class TStack {
 private:
  std::array<T, kStackSize> data;
  int topIndex;

 public:
  TStack() : topIndex(-1) {}
  bool empty() const {
    return topIndex < 0;
  }
  bool full() const {
    return topIndex >= kStackSize - 1;
  }
  void push(const T& item) {
    if (full()) {
      throw std::runtime_error("Error: Stack overflow");
    }
    data.at(++topIndex) = item;
  }
  void pop() {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    --topIndex;
  }
  T& top() {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    return data.at(topIndex);
  }
  const T& top() const {
    if (empty()) {
      throw std::runtime_error("Error: stack is empty");
    }
    return data.at(topIndex);
  }
};
#endif  // INCLUDE_TSTACK_H_
