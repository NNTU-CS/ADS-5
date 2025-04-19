// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kSize>
class TStack {
 private:
  T data[kSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& value) {
    if (topIndex >= kSize - 1)
      throw std::overflow_error("Stack overflow");
    data[++topIndex] = value;
  }

  T pop() {
    if (isEmpty())
      throw std::underflow_error("Stack underflow");
    return data[topIndex--];
  }

  T top() const {
    if (isEmpty())
      throw std::underflow_error("Stack is empty");
    return data[topIndex];
  }

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex >= kSize - 1;
  }

  void clear() {
    topIndex = -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
