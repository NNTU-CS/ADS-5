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
    void push(T value) {
      if (!isFull()) {
        data[++topIndex] = value;
      }
    }
T pop() {
  if (!isEmpty()) {
    return data[topIndex--];
  }
  return T();
}
T top() const {
  if (!isEmpty()) {
    return data[topIndex];
  }
  return T();
}
bool isEmpty() const {
  return topIndex == -1;
}
bool isFull() const {
  return topIndex == size - 1;
};

#endif  // INCLUDE_TSTACK_H_
