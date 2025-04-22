// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  T stack[size];
  int top = -1;
 public:
  TStack() : top(-1), stack{ 0 } {}

  void push(T item) {
    stack[++top] = item;
  }

  T pop() {
    if (top == -1) {
      throw("Стек пуст");
    }

    return stack[top--];
  }

  T get_item() {
    return stack[top];
  }

  int get_top() {
    return top;
  }
};

#endif  // INCLUDE_TSTACK_H_
