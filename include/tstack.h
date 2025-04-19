// Copyright 2021 NNTU‑CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int kSize>
class TStack {
 private:
  T data[kSize];
  int top;

 public:
  TStack() : top(-1) {}

  T get() const { return data[top]; }

  bool isEmpty() const { return top == -1; }

  bool isFull() const { return top == kSize - 1; }

  void pop() {
    if (top >= 0) {
      --top;
    }
  }

  void push(T val) {
    if (top < kSize - 1) {
      data[++top] = val;
    }
  }
};

#endif  // INCLUDE_TSTACK_H_
