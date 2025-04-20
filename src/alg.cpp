// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return 0;
  }
}
static inline bool isOper(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
std::string infx2pstfx(const std::string& inf) {
 std::string out;
 TStack<char, 128> ops;
 for (size_t i = 0; i < inf.size(); ++i) {
  char ch = inf[i];
  if (std::isspace(static_cast<unsigned char>(ch))) continue;
  if (std::isdigit(static_cast<unsigned char>(ch))) {
    while (i < inf.size() && std::isdigit(static_cast<unsigned char>(inf[i])))
      out += inf[i++];
    out += ' ';
    --i;
  }
  else if (ch == '(') {
    ops.push(ch);
  }
  else if (ch == ')') {
    while (!ops.isEmpty() && ops.getTop() != '(') {
      out += ops.getTop();
      out += ' ';
      ops.pop();
    }
    if (!ops.isEmpty()) ops.pop();
  }
  else if (isOper(ch)) {
    while (!ops.isEmpty() && isOper(ops.getTop()) &&
      prioritet(ops.getTop()) >= prioritet(ch)) {
      out += ops.getTop();
      out += ' ';
      ops.pop();
    }
    ops.push(ch);
  }
}
while (!ops.isEmpty()) {
  out += ops.getTop();
  out += ' ';
  ops.pop();
}
if (!out.empty() && out.back() == ' ') out.pop_back();
return out;
}

int eval(const std::string& pref) {
   std::stringstream ss(post);
 std::string token;
 TStack<int, 128> st;
 while (ss >> token) {
   if (token.size() == 1 && isOper(token[0])) {
     if (st.size() < 2)
       throw std::runtime_error("incorrect postfix expression");
     int rhs = st.getTop();
     st.pop();
     int lhs = st.getTop();
     st.pop();
     switch (token[0]) {
     case '+':
       st.push(lhs + rhs);
       break;
     case '-':
       st.push(lhs - rhs);
       break;
     case '*':
       st.push(lhs * rhs);
       break;
     case '/':
       st.push(lhs / rhs);
       break;
     }
   }
   else {
     st.push(std::stoi(token));
   }
 }
 if (st.size() != 1) throw std::runtime_error("incorrect postfix expression");
 return st.getTop();
  return 0;
}
