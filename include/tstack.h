// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, const int size>
class TStack {
  T data[100];
  int m;

 public:
  TStack() {
    m = 0;
  }
  void map(const T& item) {
    if (m <= size - 1)
      data[m++] = item;
    else
      throw std::string("Full stack");
  }
  T rok() {
    if (m > 0)
      return data[--m];
    else
      throw std::string("Empty stack");
  }
  T see() {
    if (m > 0)
      return data[m-1];
    else
      return -1;
  }
};
#endif  // INCLUDE_TSTACK_H_
