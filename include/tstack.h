// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T data[size] = {};
  int top = -1;
 public:
  TStack() : top(-1) {}
  void push(const T& value) {
    if (top < size - 1) {
      data[++top] = value;
    }
  }
  T pop() {
    return top >= 0 ? data[top--] : T();
  }
  T Top() const {
    return top >= 0 ? data[top] : T();
  }
  bool empty() const {
    return top == -1;
  }
};
#endif  // INCLUDE_TSTACK_H_
