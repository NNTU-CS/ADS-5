// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T arr[size] = { 100 };
  int index;

 public:
  Tstack() : index(-1) {}
  bool isempty() const {
    return index < 0;
  }
  bool isfull() const {
    return index > size - 1;
  }
  void push(const T& elem) {
    if (isfull()) {
      throw std::runtime_error("Stack is full");
    }
    arr[++index] = elem;
  }
  void pop() {
    if (isempty()) {
      throw std::runtime_error("Stack is empty");
    }
    index--;
  }
  const T& top() const {
    if (isempty()) {
      throw std::runtime_error("Stack is empty");
    }
    return arr[index];
  }
};

#endif  // INCLUDE_TSTACK_H_
