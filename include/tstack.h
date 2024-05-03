// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>
#include <string>

template<typename T, int size>
class TStack {
 public:
  TStack() : top(-1) {
    arr = new T[size];
  }
  void push(const T& item) {
    if (top <= size - 1)
      arr[++top] = item;
    else
      throw std::string("stack is full");
  }
  T pop() {
    if (isEmpty())
      throw std::string("stack is empty");
    else
      return arr[top--];
  }
  ~TStack() {
    delete[] arr;
  }
  bool isEmpty() const {
    return top == -1;
  }
  T get() const {
    if (isEmpty())
      throw std::string("stack is empty");
    else
      return arr[top];
  }
 private:
  T* arr;
  int top;
};
#endif  // INCLUDE_TSTACK_H_
