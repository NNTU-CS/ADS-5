// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

template<typename T, size_t SIZE>
class TStack {
private:
    T items[SIZE];
    int topIndex;
public:
    TStack() : topIndex(-1) {}
    void push(T item) {
        if (topIndex >= SIZE - 1) throw std::overflow_error("Stack overflow");
        items[++topIndex] = item;
    }
    T pop() {
        if (topIndex < 0) throw std::underflow_error("Stack underflow");
        return items[topIndex--];
    }
    bool isEmpty() const {
        return topIndex < 0;
    }
    T top() const {
        if (topIndex < 0) throw std::underflow_error("Stack is empty");
        return items[topIndex];
    }
};

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string output;
  std::string num;
  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];
    if (isdigit(c)) {
      num += c;
    } else {
      if (!num.empty()) {
        output += num + ' ';
        num.clear();
      }
      if (c == '(') {
        stack.push(c);
      } else if (c == ')') {
        while (!stack.isEmpty() && stack.top() != '(') {
          output += stack.pop();
          output += ' ';
        }
        stack.pop();
      } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        while (!stack.isEmpty() && priority(stack.top()) >= priority(c)) {
          output += stack.pop();
          output += ' ';
        }
        stack.push(c);
      }
    }
  }
  if (!num.empty()) {
    output += num + ' ';
  }
  while (!stack.isEmpty()) {
    output += stack.pop();
    output += ' ';
  }
  if (!output.empty() && output.back() == ' ')
    output.pop_back();
  return output;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0])) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.pop();
      int a = stack.pop();
      int res = 0;
      switch (token[0]) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
      }
      stack.push(res);
    }
  }
  return stack.pop();
}
