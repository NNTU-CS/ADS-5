// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  private:
    static constexpr int kStackSize = size;
    T arr[kStackSize];
    int top;
  public:
    TStack() : top(-1) {}
    void push(const T& val) {
      if (top >= size - 1)
        throw std::overflow_error("Stack overflow");
      arr[++top] = val;
    }
    T pop() {
      if (isEmpty())
        throw std::underflow_error("Stack underflow");
      return arr[top--];
    }
    T peek() const {
      if (isEmpty())
        throw std::underflow_error("Stack underflow");
      return arr[top];
    }
    bool isEmpty() const {
      return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
