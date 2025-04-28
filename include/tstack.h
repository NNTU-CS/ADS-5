// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <stdexcept>

template <typename T, int kSize>
class TStack {
 public:
  TStack() : top_(-1) {}

  void Push(const T& value) {
    if (IsFull()) {
      throw std::overflow_error("stack overflow");
    }
    data_[++top_] = value;
  }

  T Pop() {
    if (IsEmpty()) {
      throw std::underflow_error("stack underflow");
    }
    return data_[top_--];
  }

  const T& Top() const {
    if (IsEmpty()) {
      throw std::underflow_error("stack is empty");
    }
    return data_[top_];
  }

  bool IsEmpty() const { return top_ == -1; }
  bool IsFull()  const { return top_ + 1 == kSize; }
  int  Size()    const { return top_ + 1; }

 private:
  T   data_[kSize];
  int top_;
};

#endif  // INCLUDE_TSTACK_H_
