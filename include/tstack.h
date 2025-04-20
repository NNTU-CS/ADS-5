// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
  static const int max_size = size;
  T arr[max_size];
  int top;
public:
  TStack() : top(-1) {}
  bool isEmpty() const {
    return top == -1;
  }
  bool isFull() const {
    return top == max_size - 1;
  }
  T getTop() const {
    if (isEmpty()) {
      throw std::out_of_range("Stack is emty");
    } return arr[top];
  }
  void push(const T& value) {
    if (isFull()) {
      throw std::overflow_error("Stack is full");
    } arr[++top] = value;
  }
  void pop() {
    if (isEmpty()) {
      throw std::underflow_error("Stack is empty");
    } --top;
  }
  int size() const {
    return top + 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
