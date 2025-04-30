// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack 
{

private:
  T* array;
  int top;

public:
  TStack(): array(new T[size]), top(-1) {}
~TStack() {
  delete[] array;
}
bool is_empty() const {
  return top == -1;
}
bool is_full() const {
  return top == ( size - 1 );
}
void push(const T& n) {
  if (!is_full())
    array[++top] = n;
}
void pop() {
  if (!is_empty())
    top--;
}
T peek() const {
  if (!is_empty())
    return array[top];
  else
    return T();
}

#endif  // INCLUDE_TSTACK_H_
