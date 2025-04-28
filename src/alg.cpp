// Copyright 2025 NNTU-CS
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

#include "tstack.h"

namespace details {

// Checks if the character is one of the supported operators.
inline bool IsOperator(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }

// Classical precedence (the higher – the tighter binds)
inline int Precedence(char op) {
  switch (op) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    case '^':
      return 3;
    default:
      return 0;
  }
}

// Executes the binary operation `lhs op rhs`.
inline int Apply(int lhs, int rhs, char op) {
  switch (op) {
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;  // integer division as per task
    case '^': {
      int res = 1;
      for (int i = 0; i < rhs; ++i) res *= lhs;
      return res;
    }
    default:
      throw std::invalid_argument("unknown operator");
  }
}

}  // namespace details

//------------------------------------------------------------------------------
// Converts infix expression → postfix (Reverse Polish Notation).
//------------------------------------------------------------------------------
std::string infx2pstfx(const std::string& inf) {
  std::string       out;
  TStack<char, 128> ops;

  for (size_t i = 0; i < inf.size();) {
    char ch = inf[i];

    if (std::isspace(static_cast<unsigned char>(ch))) {
      ++i;
      continue;
    }

    if (std::isdigit(static_cast<unsigned char>(ch))) {
      std::string number;
      while (i < inf.size() && std::isdigit(static_cast<unsigned char>(inf[i]))) {
        number.push_back(inf[i++]);
      }
      out += number + ' ';
      continue;
    }

    if (ch == '(') {
      ops.Push(ch);
      ++i;
      continue;
    }

    if (ch == ')') {
      while (!ops.IsEmpty() && ops.Top() != '(') {
        out.push_back(ops.Pop());
        out.push_back(' ');
      }
      if (ops.IsEmpty()) throw std::invalid_argument("mismatched parentheses");
      ops.Pop();  
      ++i;
      continue;
    }

    if (details::IsOperator(ch)) {
      while (!ops.IsEmpty() && details::IsOperator(ops.Top()) &&
             details::Precedence(ops.Top()) >= details::Precedence(ch)) {
        out.push_back(ops.Pop());
        out.push_back(' ');
      }
      ops.Push(ch);
      ++i;
      continue;
    }

    throw std::invalid_argument(std::string("unexpected symbol: ") + ch);
  }

  while (!ops.IsEmpty()) {
    if (ops.Top() == '(') throw std::invalid_argument("mismatched parentheses");
    out.push_back(ops.Pop());
    out.push_back(' ');
  }

  if (!out.empty()) out.pop_back(); 
  return out;
}

int eval(const std::string& post) {
  std::istringstream iss(post);
  std::string        token;
  TStack<int, 128>   st;

  while (iss >> token) {
    if (std::isdigit(static_cast<unsigned char>(token[0]))) {
      st.Push(std::stoi(token));
      continue;
    }

    if (token.size() == 1 && details::IsOperator(token[0])) {
      if (st.Size() < 2) throw std::invalid_argument("insufficient operands");
      int rhs = st.Pop();
      int lhs = st.Pop();
      st.Push(details::Apply(lhs, rhs, token[0]));
      continue;
    }

    throw std::invalid_argument("invalid token: " + token);
  }

  if (st.Size() != 1) throw std::invalid_argument("expression error");
  return st.Pop();
}
