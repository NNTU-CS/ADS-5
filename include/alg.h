// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T data[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool isEmpty() const {
    return topIndex == -1;
  }

  bool isFull() const {
    return topIndex == size - 1;
  }

  void push(const T& element) {
    if (isFull()) {
      std::cerr << "Stack Overflow!" << std::endl;
      return;
    }
    data[++topIndex] = element;
  }

  T pop() {
    if (isEmpty()) {
      std::cerr << "Stack Underflow!" << std::endl;
      return T();
    }
    return data[topIndex--];
  }

  T top() const {
    if (isEmpty()) {
      std::cerr << "Stack is Empty!" << std::endl;
      return T();
    }
    return data[topIndex];
  }

  int get_size() const {
    return size;
  }
};

#endif  // INCLUDE_TSTACK_H_
