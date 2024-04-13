// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  T* stackArray;
  int top;

 public:
  TStack() {
    stackArray = new T[size];
    top = -1;
  }

  ~TStack() { delete[] stackArray; }

  void push(T value) {
    if (top >= size - 1) {
      throw "Stack overflow";
    }
    stackArray[++top] = value;
  }

  T pop() {
    if (top < 0) {
      throw "Stack is empty";
    }
    return stackArray[top--];
  }

  T get() {
    if (top < 0) {
      throw "Stack is empty";
    }
    return stackArray[top];
  }

  bool isEmpty() { return (top == -1); }
};

#endif  // INCLUDE_TSTACK_H_
