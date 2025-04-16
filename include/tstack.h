// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int kMaxSize>
class TStack {
 private:
  T data[kMaxSize];
  int top;

 public:
  TStack() : top(-1) {}

  bool isEmpty() const {
    return top == -1;
  }

  bool isFull() const {
    return top == kMaxSize - 1;
  }

  void push(T value) {
    if (!isFull()) {
      data[++top] = value;
    }
  }

  T pop() {
    if (!isEmpty()) {
      return data[top--];
    }
    return T();
  }

  T peek() const {
    if (!isEmpty()) {
      return data[top];
    }
    return T();
  }
};

#endif  // INCLUDE_TSTACK_H_
