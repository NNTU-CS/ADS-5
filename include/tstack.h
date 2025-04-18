// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int MSSize>
class TStack {
 private:
T arr[MSSize];
int top;
 public:
TStack() :top(-1) {}
T get() const {
return arr[top];
}
bool isFull() const {
return top == MSSize - 1;
}
bool isEmpty() const {
return top == -1;
}
void push(T item) {
if (top < MSSize - 1)
arr[++top] = item;
}
void pop() {
if (top >= 0)
top--;
}
};
#endif  // INCLUDE_TSTACK_H_
