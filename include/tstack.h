// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
  static const int StackSize = size;
  T data[StackSize];
  int topIndex;

public:
  TStack() : topIndex(-1) {}
  bool isEmpty() const {
    return topIndex == -1;
  }
  void push(const T& value) {
    if (topIndex < StackSize - 1) data[++topIndex] = value;
  }
  T pop() {
    if (topIndex >= 0) return data[topIndex--];
    return T();
  }
  T top() const {
    if (topIndex >= 0) return data[topIndex];
    return T();
  }
};
#endif  // INCLUDE_TSTACK_H_
