// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
static int precedence(char op) {
  return (op == '+' || op == '-') ? 1 :
    (op == '*' || op == '/') ? 2 : 0;
}
static inline bool isOp(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
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
      while (!ops.empty() && ops.top() != '(') {
        out += ops.top(); out += ' '; ops.pop();
      }
      if (!ops.empty()) ops.pop();                              
    }
    else if (isOp(ch)) {                                       
      while (!ops.empty() && isOp(ops.top()) &&
        precedence(ops.top()) >= precedence(ch)) {
        out += ops.top(); out += ' '; ops.pop();
      }
      ops.push(ch);
    }
  }
  while (!ops.empty()) { out += ops.top(); out += ' '; ops.pop(); }
  if (!out.empty() && out.back() == ' ') out.pop_back();
  return out;
}
int eval(const std::string& post) {
  std::stringstream ss(post);
  std::string token;
  TStack<int, 128> st;
  while (ss >> token) {
    if (token.size() == 1 && isOp(token[0])) {                    
      if (st.size() < 2) throw std::runtime_error("incorrect postfix");
      int rhs = st.top(); st.pop();
      int lhs = st.top(); st.pop();
      switch (token[0]) {
      case '+': st.push(lhs + rhs); break;
      case '-': st.push(lhs - rhs); break;
      case '*': st.push(lhs * rhs); break;
      case '/': st.push(lhs / rhs); break;      
      }
    }
    else {                                        
      st.push(std::stoi(token));
    }
  }
  if (st.size() != 1) throw std::runtime_error("incorrect postfix");
  return st.top();
}
