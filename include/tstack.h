// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
  // добавьте код стека
private:
    T data[100];
    int top;

 public:
    TStack(): top(-1) {}
    void push(T val) {
      if (!isOverflow())
        data[++top] = val;
      else
        throw std::string("Full");
    }
    T see() const { return data[top]; }
    T pop() {
      if (isEmpty())
        throw std::string("Empty");
      else
        return data[top--];
    }
    bool isOverflow() const {
      return top == size - 1;
    }
    bool isEmpty() const {
      return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
