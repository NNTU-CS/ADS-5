// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <vector>

template<typename T, int MSSize>
class TStack {
 private:
std::vector<T> data;
int top;

 public:
TStack() : top(-1) {}
bool isEmpty() const {
return top == -1;
}
bool isFull() const {
return top == MSSize - 1;
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
};
#endif  // INCLUDE_TSTACK_H_
