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
void push(const T& value) {
  if (topIndex < size - 1) {
    data[++topIndex] = value;
  }
}
void pop() {
  if (!empty()) {
    topIndex--;
  }
}
T top() const {
  if (!empty()) {
    return data[topIndex];
  }
  return T();
}
bool empty() const {
  return topIndex == -1;
}
bool isFull() const {
  return topIndex == size - 1;
}
};
#endif  // INCLUDE_TSTACK_H_
