// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    T data[100];
    int top;

 public:
    TStack() :top(0) {}
    void push(const T& item) {
      if (top <= size - 1) {
        data[top++] = item;
      } else {
          throw std::string("is full");
      }
    }
    T get() {
      if (top > 0) {
        return data[top - 1];
      } else {
          throw std::string("is empty");
      }
    }
    T pop() {
      if (top > 0) {
        top--;
        return data[top];
      } else {
          throw std::string("is empty");
      }
    }
    bool IsEmpty() {
      return top == 0;
    }
};
#endif  // INCLUDE_TSTACK_H_
