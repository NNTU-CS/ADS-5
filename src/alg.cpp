#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"
int priority(char op) {
  switch (op) {
    case '*': case '/': return 3;
    case '+': case '-': return 2;
    default: return 1;
  }
}
bool checkIfOperator(char cha) {
  return cha == '+' || cha == '-' || cha == '*' || cha == '/';
}
std::string infx2pstfx(const std::string& infix) {
  TStack<char, 100> operators;
  std::string postfix;
  for (size_t i = 0; i < infix.size(); ++i) {
    char cha = infix[i];
    if (std::isspace(cha)) continue;
    if (std::isdigit(cha)) {
      while (i < infix.size() && std::isdigit(infix[i])) {
        postfix += infix[i++];
      }
      postfix += ' ';
      i--;
    } else if (cha == '(') {
      operators.push(cha);
    } else if (cha == ')') {
      while (operators.hasElements() && operators.check() != '(') {
        postfix += operators.remove();
        postfix += ' ';
      }
      operators.remove(); // Remove '('
    } else if (checkIfOperator(cha)) {
      while (operators.hasElements() &&
             priority(operators.check()) >= priority(cha)) {
        postfix += operators.remove();
        postfix += ' ';
      }
      operators.push(cha);
    }
  }
  while (operators.hasElements()) {
    postfix += operators.remove();
    postfix += ' ';
  }
  if (!postfix.empty() && postfix.back() == ' ') {
    postfix.pop_back();
  }
  return postfix;
}
int eval(const std::string& postfix) {
  TStack<int, 100> numbers;
  std::istringstream iss(postfix);
  std::string token;
  while (iss >> token) {
    if (std::isdigit(token[0])) {
      numbers.push(std::stoi(token));
    } else if (checkIfOperator(token[0])) {
      int a = numbers.remove();
      int t = numbers.remove();
      switch (token[0]) {
        case '+': numbers.push(t + a); break;
        case '-': numbers.push(t - a); break;
        case '*': numbers.push(t * a); break;
        case '/': numbers.push(t / a); break;
      }
    }
  }
  return numbers.remove();
}
