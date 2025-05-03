// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
template <typename T, int SIZE>
class TStack {
 private:
  T data[SIZE];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}
  bool isEmpty() const { return topIndex == -1; }
  bool isFull() const { return topIndex == SIZE - 1; }

  void push(const T& value) {
    if (!isFull()) data[++topIndex] = value;
  }

  T pop() {
    return isEmpty() ? T() : data[topIndex--];
  }

  T peek() const {
    return isEmpty() ? T() : data[topIndex];
  }
};
#endif  // INCLUDE_TSTACK_H_
