// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <vector>

template<typename T, int MSSize>
class TStack {
 private:
std::vector<T> arr;
int top;
 public:
TStack() : top(-1), arr(MSSize) {}
T get() const {
if (top >= 0) {
return arr[top];
} else {
throw std::out_of_range("Stack is empty");
}
}
bool isFull() const {
return top == MSSize - 1;
}
bool isEmpty() const {
return top == -1;
}
void push(const T& item) {
if (top < MSSize - 1) {
arr[++top] = item;
} else {
throw std::overflow_error("Stack overflow");
}
}
void pop() {
if (top >= 0) {
top--;
} else {
throw std::underflow_error("Stack underflow");
}
}
};
#endif  // INCLUDE_TSTACK_H_
