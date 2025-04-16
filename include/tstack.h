// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template<typename T, int kMaxSize>
class TStack {
 private:
  T items[kMaxSize];
  int index;

 public:
  TStack() : index(-1) {}

  void push(const T& value) {
    if (index >= kMaxSize - 1) {
      throw std::string("Стек переполнен");
    }
    items[++index] = value;
  }

  T pop() {
    if (isEmpty()) {
      throw std::string("В стеке ничего нет");
    }
    return items[index--];
  }

  T getTop() const {
    if (isEmpty()) {
      throw std::string("В стеке ничего нет");
    }
    return items[index];
  }

  bool isEmpty() const {
    return index == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
