// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template<typename ElementType, int Capacity>
class TStack {
 public:
  TStack() : pointer(-1) {}

  bool isVoid() const {
    return pointer == -1;
  }

  bool isFull() const {
    return pointer == Capacity - 1;
  }

  void add(const ElementType& value) {
    if (isFull()) {
      throw std::overflow_error("Stack overflow");
    }
    storage[++pointer] = value;
  }

  ElementType remove() {
    if (isVoid()) {
      throw std::underflow_error("Stack underflow");
    }
    return storage[pointer--];
  }

  ElementType getTop() const {
    if (isVoid()) {
      throw std::underflow_error("Stack empty");
    }
    return storage[pointer];
  }

 private:
  ElementType storage[Capacity];
  int pointer;
};

#endif  // INCLUDE_TSTACK_H_
