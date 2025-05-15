// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kSize>
class TStack {
  T data[kSize];
  int topIndex;

public:
  TStack() : topIndex(-1) {}

  void push(const T& value) {
    if (topIndex < kSize - 1) {
      data[++topIndex] = value;
    }
  }

  void pop() {
    if (topIndex >= 0) {
      --topIndex;
    }
  }

  T top() const {
    return data[topIndex];
  }

  bool isEmpty() const {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
