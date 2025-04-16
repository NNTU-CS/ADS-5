// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int Size>
class TStack {

 private:
  T arr[Size];
  int top;

 public:
  TStack() : top(-1) { }

  void push(const T& val) {
    if (top < Size - 1) {
      arr[++top] = val;
    }
  }

  T pop() {
    if (top >= 0) {
      return arr[top--];
    }
    return T();
  }

  T peek() const {
    if (top >= 0) {
      return arr[top];
    }
    return T();
  }

  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == Size - 1;
  }
};

#endif  // INCLUDE_TSTACK_H_
