// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>

template <typename T, int SIZE>
class TStack {
 private:
  T storage[SIZE];
  int index;

 public:
  TStack() : index(-1) {
    for (int i = 0; i < SIZE; ++i) {
      storage[i] = T();
    }
  }

  void push(const T& item) {
    if (index < SIZE - 1) {
      storage[++index] = item;
    }
  }

  T pop() {
    if (index >= 0) {
      return storage[index--];
    }
    return T();
  }

  T top() const {
    if (index >= 0) {
      return storage[index];
    }
    return T();
  }

  bool isEmpty() const {
    return index == -1;
  }
};

std::string infx2pstfx(const std::string& expression) {
  TStack<char, 100> opStack;
  std::string postfix;
  std::map<char, int> priority = {
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
  };

  for (size_t i = 0; i < expression.size(); ++i) {
    char sym = expression[i];

    if (isdigit(sym)) {
      while (i < expression.size() && isdigit(expression[i])) {
        postfix += expression[i++];
      }
      postfix += ' ';
      --i;
    } else if (sym == '(') {
      opStack.push(sym);
    } else if (sym == ')') {
      while (!opStack.isEmpty() && opStack.top() != '(') {
        postfix += opStack.pop();
        postfix += ' ';
      }
      opStack.pop(); // удаляем '('
    } else if (priority.count(sym)) {
      while (!opStack.isEmpty() && opStack.top() != '(' &&
             priority[opStack.top()] >= priority[sym]) {
        postfix += opStack.pop();
        postfix += ' ';
      }
      opStack.push(sym);
    }
  }

  while (!opStack.isEmpty()) {
    postfix += opStack.pop();
    postfix += ' ';
  }

  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }

  return postfix;
}

int eval(const std::string& postfix) {
  TStack<int, 100> calcStack;
  std::string buffer;

  for (char sym : postfix) {
    if (isdigit(sym)) {
      buffer += sym;
    } else if (sym == ' ' && !buffer.empty()) {
      calcStack.push(std::stoi(buffer));
      buffer.clear();
    } else if (sym == '+' || sym == '-' || sym == '*' || sym == '/') {
      int operand2 = calcStack.pop();
      int operand1 = calcStack.pop();
      switch (sym) {
        case '+': calcStack.push(operand1 + operand2); break;
        case '-': calcStack.push(operand1 - operand2); break;
        case '*': calcStack.push(operand1 * operand2); break;
        case '/': calcStack.push(operand1 / operand2); break;
      }
    }
  }

  return calcStack.pop();
}
