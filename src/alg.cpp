// Copyright 2025 NNTU-CS
#include <cctype>
#include <string>

#include "tstack.h"

class ExpressionConverter {
 private:
  static bool isMathChar(char ch) {
    const char ops[] = {'+', '-', '*', '/'};
    for (char op : ops) {
      if (ch == op) return true;
    }
    return false;
  }

  static int getOpWeight(char op) {
    const int LOW = 1, HIGH = 2;
    return (op == '+' || op == '-') ? LOW : (op == '*' || op == '/') ? HIGH : 0;
  }

  static int compute(int first, int second, char operation) {
    switch (operation) {
      case '+':
        return first + second;
      case '-':
        return first - second;
      case '*':
        return first * second;
      case '/':
        return first / second;
      default:
        return 0;
    }
  }

 public:
  static std::string convertInfix(const std::string& expr) {
    TStack<char, 100> opStack;
    std::string output;
    bool needsSpace = false;

    for (char ch : expr) {
      if (isspace(ch)) continue;

      if (isdigit(ch)) {
        output += ch;
        needsSpace = true;
      } else {
        if (needsSpace) {
          output += ' ';
          needsSpace = false;
        }

        if (ch == '(') {
          opStack.push(ch);
        } else if (ch == ')') {
          while (!opStack.isEmpty() && opStack.peek() != '(') {
            output += opStack.pop();
            output += ' ';
          }
          opStack.pop();
        } else if (isMathChar(ch)) {
          while (!opStack.isEmpty() &&
                 getOpWeight(opStack.peek()) >= getOpWeight(ch)) {
            output += opStack.pop();
            output += ' ';
          }
          opStack.push(ch);
        }
      }
    }

    if (needsSpace) output += ' ';

    while (!opStack.isEmpty()) {
      output += opStack.pop();
      output += ' ';
    }

    if (!output.empty() && output.back() == ' ') {
      output.pop_back();
    }

    return output;
  }

  static int evaluate(const std::string& expr) {
    TStack<int, 100> numStack;

    for (char ch : expr) {
      if (isspace(ch)) continue;

      if (isdigit(ch)) {
        numStack.push(ch - '0');
      } else if (isMathChar(ch)) {
        int b = numStack.pop();
        int a = numStack.pop();
        numStack.push(compute(a, b, ch));
      }
    }

    return numStack.pop();
  }
};

std::string infx2pstfx(const std::string& inf) {
  return ExpressionConverter::convertInfix(inf);
}

int eval(const std::string& post) {
  return ExpressionConverter::evaluate(post);
}
