// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T stack[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == size - 1;
  }

  void push(const T& value) {
    if (!isFull()) {
      stack[++topIndex] = value;
    } else {
      throw std::out_of_range("Stack is full");
    }
  }

  void pop() {
    if (!isEmpty()) {
      --topIndex;
    } else {
      throw std::out_of_range("Stack is empty");
    }
  }

  T top() const {
    if (!isEmpty()) {
      return stack[topIndex];
    } else {
      throw std::out_of_range("Stack is empty");
    }
  }

  int currentSize() const {
    return topIndex + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
