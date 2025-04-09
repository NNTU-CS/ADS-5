// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  T* arr;
  int top;

 public:
  TStack() {
    arr = new T[size];
    top = -1;
  }

  bool isEmpty() const { return top == -1; }

  bool isFull() const { return top == size - 1; }

  void push(T& el) {
    if (!isFull()) {
      arr[++top] = el;
    }
  }

  T get() const {
    if (!isEmpty()) {
      return arr[top];
    }
    return T();
  }

  void pop() {
    if (!isEmpty()) {
      --top;
    }
  }
};

#endif  // INCLUDE_TSTACK_H_
