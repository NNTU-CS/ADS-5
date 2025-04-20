// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int size>
class TStack {
 private:
  T arr[size] = { 100 };
  int index;
 public:
  TStack() : index(-1) {}
  bool isEmpty() const {
    return index < 0;
  }
  bool isFull() const {
    return index > size - 1;
  }
  void push(const T& elem) {
    if (isfull()) {
      throw std::runtime_error("Stack is full");
    }
    arr[++index] = elem;
  }
  void pop() {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty");
    }
    index--;
  }
  const T& top() const {
    if (isEmpty()) {
      throw std::runtime_error("Stack is empty");
    }
    return arr[index];
  }
};

};
#endif  // INCLUDE_TSTACK_H_
