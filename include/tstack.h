// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  // добавьте код стека
public:
TStack() {
  data = new T[size];
  topIndex = -1;
}
~TStack() {
  delete[] data;
}
bool isEmpty() const {
  return topIndex == size - 1;
}
bool isFull() const {
  return topIndex == size - 1;
}
void push(const T &value) {
  if (isFull()) {
    throw std::overflow_error("Stack is full");
  }
  data[++topIndex] = value;
}
T pop() {
  if (isEmpty()) {
    throw std::underflow_error("Stack is empty");
  }
  return data[topIndex--];
}
T get() const {
  if (isEmpty()) {
    throw std::underflow_error("Stack is empty");
  }
  private;
  T *data;
  int topIndex;
};

#endif  // INCLUDE_TSTACK_H_
