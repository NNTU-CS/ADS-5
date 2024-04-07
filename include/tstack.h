// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  T *data = new T[size];
  int top = 0;

 public:
  TStack() {
    top = 0;
  }
  ~TStack() { delete[] data; }
  void push(T item) {
    data[top] = item;
    top++;
  }
  T pop() {
    if (top == 0) {
      throw "Stack is empty!";
    } else {
      top -= 1;
      return data[top];
    }
  }
  T check() {
    if (top == 0) {
      throw "Stack is empty!";
    } else {
      return data[top - 1];
    }
  }
  bool isempty() {
    return top == 0;
  }
};
#endif  // INCLUDE_TSTACK_H_
