// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>

template <typename T, int size>
class TStack {
 private:
  T arr[size];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& value) {
    if (topIndex >= size - 1) throw "Stack overflow";
    arr[++topIndex] = value;
  }

  T pop() {
    if (topIndex < 0) throw "Stack underflow";
    return arr[topIndex--];
  }

  T top() const {
    if (topIndex < 0) throw "Stack is empty";
    return arr[topIndex];
  }

  bool isEmpty() const {
    return topIndex < 0;
  }
};

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& infx) {
  std::string output;
  TStack<char, 100> opStack;

  for (char c : infx) {
    if (isdigit(c)) {
      output += c;
    } else if (c == '(') {
      opStack.push(c);
    } else if (c == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        output += opStack.pop();
      }
      if (!opStack.isEmpty()) opStack.pop();  // Удаляем '('
    } else {
      while (!opStack.isEmpty() && priority(opStack.top()) >= priority(c)) {
        output += opStack.pop();
      }
      opStack.push(c);
    }
  }

  while (!opStack.isEmpty()) {
    output += opStack.pop();
  }

  return output;
}

int eval(const std::string& pstfx) {
  TStack<int, 100> valStack;

  for (char c : pstfx) {
    if (isdigit(c)) {
      valStack.push(c - '0');
    } else {
      int b = valStack.pop();
      int a = valStack.pop();
      switch (c) {
        case '+': valStack.push(a + b); break;
        case '-': valStack.push(a - b); break;
        case '*': valStack.push(a * b); break;
        case '/': valStack.push(a / b); break;
      }
    }
  }

  return valStack.pop();
}
