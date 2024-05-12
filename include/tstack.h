// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  // добавьте код стека
};
  private:
  T data[300];
  int top;
  public:
  Tstack() : top(0) {}
  void push(const T &item) {
    if (top <= size - 1) {
      data[top++] = item;
    } else {
      throw std::string("стек переполненный");
    }
  } 
  T pop() {
    if (top > 0) {
      return data[--top];
    } else {
      throw std::string("стек пустой");
    }
  }
  T get() const {
    if (top > 0) {
      return data[top - 1];
    } else {
      throw std::string("пусто");
    }
  }
  bool isEmpty() const {
    return top == 0;
  }
};


#endif  // INCLUDE_TSTACK_H_
