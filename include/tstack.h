// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
  static constexpr int dataSize = size;
  T data[dataSize];
  int top;

 public:
  Tstack() : top(-1) {}
  bool isEmpty() const {
    return top == -1;
  }
  bool isFull() const {
    return top == size - 1;
  }
  T get() const {
    if (!isEmpty())
      return data[top];
    else
      throw std::string("Empty");
  }
  void push(const T& item) {
    if (!isFull())
      data[++top] = item;
    else
      throw std::string("Full");
  }
  void pop() {
    if (!isEmpty())
      return data[top--];
    else
      throw std::string("Empty");
  }
};

#endif  // INCLUDE_TSTACK_H_
