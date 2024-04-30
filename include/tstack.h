// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* stackArray;
    int top;
 public:
    TStack() : top(-1) {
      stackArray = new T[size];
    }
    void pop() {
      if (top >= 0)
        top--;
    }
    void push(T item) {
      if (top < size - 1)
        stackArray[++top] = item;
    }
    T get() const {
      return stackArray[top];
    }
    bool checkEmpty() const {
      return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
