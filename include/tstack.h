// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
  T items[size];
  int index;

public:
  TStack() : index(-1) {}

  void push(const T& value) {
    if (index >= size - 1) {
      throw std::string("Stack overflow");
    }
    items[++index] = value;
  }

  T pop() {
    if (isEmpty()) {
      throw std::string("Stack is empty");
    }
    return items[index--];
  }

  T getTop() const {
    if (isEmpty()) {
      throw std::string("Stack is empty");
    }
    return items[index];
  }

  bool isEmpty() const {
    return index == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_