// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <array>
#include <stdexcept>

template <typename T, int size>
class TStack {
 private:
  static constexpr int kStackSize = size;
  std::array<T, kStackSize> data_;
  int top_{-1};

 public:
  void push(const T& value) {
    if (full()) throw std::overflow_error("stack overflow");
    data_[++top_] = value;
  }

  void pop() {
    if (empty()) throw std::underflow_error("stack underflow");
    --top_;
  }

  T& top() {
    if (empty()) throw std::underflow_error("stack empty");
    return data_[top_];
  }
  const T& top() const {
    if (empty()) throw std::underflow_error("stack empty");
    return data_[top_];
  }

  int size() const { return top_ + 1; }
  bool empty() const { return top_ < 0; }
  bool full() const { return top_ == kStackSize - 1; }
};

#endif  // INCLUDE_TSTACK_H_
