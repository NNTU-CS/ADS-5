// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <array>
#include <stdexcept>

template <typename DataType, int StackSize>
class Stack {
 private:
  static_assert(StackSize > 0, "Stack size must be a positive value");
  static constexpr int kMaxStackSize = StackSize; 

  std::array<DataType, kMaxStackSize> items;  
  int headIndex;                              

 public:
  Stack() : headIndex(-1) {}

  void push(const DataType& item) {
    if (isFull()) {
      throw std::overflow_error("Stack is full: overflow");
    }
    items[++headIndex] = item;
  }

  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty: underflow");
    }
    --headIndex;
  }

  DataType& peek() {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return items[headIndex];
  }

  const DataType& peek() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return items[headIndex];
  }

  size_t size() const { return headIndex + 1; }
  bool isEmpty() const { return headIndex < 0; }
  bool isFull() const { return headIndex == kMaxStackSize - 1; }
};

#endif  // INCLUDE_TSTACK_H_
