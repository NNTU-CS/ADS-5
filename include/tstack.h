// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
  #define INCLUDE_TSTACK_H_
#include <string>
template<typename T, const int size>
class TStack {
  T data[100];
  int top;

 public:
  TStack() {
    top = 0;
  }
  void Push(const T& item) {
    if (top <= size - 1)
      data[top++] = item;
    else
      throw std::string("Is_Full!");
  }
  T Pop() {
    if (top > 0)
      return data[--top];
    else
      throw std::string("Is_Empty!");
  }
  T ViewTop() {
    if (top > 0)
      return data[top-1];
    else
      return -1;
  }
};
#endif  // INCLUDE_TSTACK_H_
