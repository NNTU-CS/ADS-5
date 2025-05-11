// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T* arr;
  int top;
  int capacity;

public:
  TStack() : top(-1), capacity(size) {
    arr = new T[capacity];
  }

  ~TStack() {
    delete[] arr;
  }

  void push(const T& value) {
    if (top == capacity - 1) {
      throw "Stack overflow!";
    }
    arr[++top] = value;
  }

  T pop() {
    if (isEmpty()) {
      std::cerr << "Error: stack underflow!\n";
    }
    return arr[top--];
  }

  T peek() const {
    if (isEmpty()) {
      std::cerr << "Error: stack is empty!\n";
    }
    return arr[top];
  }

  bool isEmpty() const {
    return top == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
