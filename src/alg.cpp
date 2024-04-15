// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

template<typename T, int size>
class TStack {
  // добавьте код стека
 private:
    T* stackArray;
    int top;
 public:
    TStack() : top(-1) {
      stackArray = new T[size];
    }
    void pop() {
      if (top >= 0)
        top--;
    }
    void push(T item) {
      if (top < size - 1)
        stackArray[++top] = item;
    }
    T get() const {
      return stackArray[top];
    }
    bool checkEmpty() const {
      return top == -1;
    }
};

std::string infx2pstfx(std::string inf) {
  std::string post = "";
  TStack<char, 100> stack;
  for (char c : inf) {
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      post += c;
      post += ' ';
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.get() != '(') {
        post += stack.get();
        post += ' ';
        stack.pop();
      }
      stack.pop();
    } else if (isOperator(c)) {
      while (!stack.isEmpty() && precedence(stack.get()) >= precedence(c)) {
        post += stack.get();
        post += ' ';
        stack.pop();
      }
      stack.push(c);
    }
  }
  while (!stack.isEmpty()) {
    post += stack.get();
    post += ' ';
    stack.pop();
  }
  return post;
}
int performOperation(int operand1, int operand2, char op) {
  switch(op) {
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      return operand1 / operand2;
    default:
      return 0;
  }
}
int eval(std::string post) {
  TStack<int, 100> stack;
  for (char c : post) {
    if (c == ' ') {
      continue;
    } else if (isdigit(c)) {
      int operand = 0;
      while (isdigit(c)) {
        operand = operand * 10 + (c - '0');
        c = *(&c + 1);
      }
      stack.push(operand);
    } else if (isOperator(c)) {
      int operand2 = stack.get();
      stack.pop();
      int operand1 = stack.get();
      stack.pop();
      int result = performOperation(operand1, operand2, c);
      stack.push(result);
    }
  }
  return stack.get();
}
