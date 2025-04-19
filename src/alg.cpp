// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>

template <typename T, int size>
class TStack {
 private:
  T data[size] = {};
  int top = -1;

 public:
  void push(const T& val) { data[++top] = val; }
  T pop() { return data[top--]; }
  T topElem() const { return data[top]; }
  bool isEmpty() const { return top == -1; }
};

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& s) {
  std::string res;
  TStack<char, 100> st;

  for (size_t i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (isdigit(c)) {
      while (i < s.size() && isdigit(s[i])) {
        res += s[i++];
      }
      res += ' ';
      --i;
    } else if (c == '(') {
      st.push(c);
    } else if (c == ')') {
      while (!st.isEmpty() && st.topElem() != '(') {
        res += st.pop();
        res += ' ';
      }
      if (!st.isEmpty()) st.pop();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      while (!st.isEmpty() && priority(st.topElem()) >= priority(c)) {
        res += st.pop();
        res += ' ';
      }
      st.push(c);
    }
  }

  while (!st.isEmpty()) {
    res += st.pop();
    res += ' ';
  }

  return res;
}

int eval(const std::string& s) {
  TStack<int, 100> st;
  std::string num;

  for (char c : s) {
    if (isdigit(c)) {
      num += c;
    } else if (c == ' ' && !num.empty()) {
      st.push(std::stoi(num));
      num.clear();
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      int b = st.pop(), a = st.pop();
      if (c == '+') st.push(a + b);
      if (c == '-') st.push(a - b);
      if (c == '*') st.push(a * b);
      if (c == '/') st.push(a / b);
    }
  }

  return st.pop();
}
