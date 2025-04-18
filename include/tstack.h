// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <vector>
#include <stdexept>
template<typename T, int kStackSize>
class TStack {
 private:
std::vector<T> data;
int top;

 public:
TStack() : top(-1), data(kStackSize) {}
bool isEmpty() const {
return top == -1;
}
bool isFull() const {
return top == kStackSize - 1;
}
void push(const T& value) {
if (!isFull()) {
data[++top] = value;
}
}
T pop() {
if (!isEmpty()) {
return data[top--];
}
return T();
}
T peek() const {
if (!isEmpty()) {
return data[top];
}
return T();
}
throw std::out_of_range("Stack is empty");
};
#endif  // INCLUDE_TSTACK_H_
