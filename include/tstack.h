// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int kSize = size;
  T data[kSize];
  int top;

 public:
  TStack() : top(-1) {}

  void push(const T& value) {
    if (top < kSize - 1)
      data[++top] = value;
  }

  void pop() {
    if (top >= 0)
      --top;
  }

  T topElement() const {
    return data[top];
  }

  bool isEmpty() const {
    return top == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
