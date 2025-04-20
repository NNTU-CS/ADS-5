// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  static_assert(N > 0, "Stack size must be greater than 0");

  private:
    std::array<T, size>
    int top;

  public:
    TStack(): top(-1) {}
    bool isEmpty()const {
      return top == -1;
    }
    bool isFull()const {
    return top == size-1;
    }
    T get()const {
      if (!isEmpty() )
        return arr[top];
     else
        throw "Empty_get";
    }
    void push(T item) {
      if (!isFull()) {
        top += 1;
        arr[top] = item;
      } else {
      throw "Full_push";
      }
    }
    void pop() {
      if (!isEmpty() )
        top -= 1;
      else
        throw "Empty_pop";
    }
    int len()const {
      return top + 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
