// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T arr[size] = { 0 };
  int top = -1;
 public:
  bool isEmpty() { return top == -1; }
  void push(char op) {
    if (top != size - 1)
      arr[++top] = op;
    else
      throw std::string("stack overflow");
  }

  T pop() { 
    if (top >= 0)
      return arr[top--];
	else
      throw std::string("stack is empty");
  }

  T getTop() const { return arr[top]; }
};

#endif  // INCLUDE_TSTACK_H_
