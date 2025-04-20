// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <array>
#include <stdexcept>

template <typename T, int N>
class TStack {
  static_assert(N > 0, "Stack size must be greater than 0");

 private:
  std::array<T, N> buffer_;
  int index_;

 public:
  TStack() : index_(-1) {}

  void push(const T& item) {
    if (isFull()) {
      throw std::overflow_error("Cannot push: stack is full");
    }
    buffer_[++index_] = item;
  }

  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("Cannot pop: stack is empty");
    }
    --index_;
  }

  T& top() {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return buffer_[index_];
  }

  const T& top() const {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    }
    return buffer_[index_];
  }

  bool isEmpty() const {
    return index_ < 0;
  }

  bool isFull() const {
    return index_ >= N - 1;
  }

  int size() const {
    return index_ + 1;
  }
};


#endif  // INCLUDE_TSTACK_H_
