#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>

int getPriority(char op) {
  if (op == '*' || op == '/') return 2;
  if (op == '+' || op == '-') return 1;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  std::stack<char> opStack;
  std::string out;

  for (size_t i = 0; i < inf.length(); ++i) {
    char ch = inf[i];

    if (std::isdigit(ch)) {
      while (i < inf.length() && std::isdigit(inf[i])) {
        out += inf[i++];
      }
      out += ' ';
      --i;
    } else if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.empty() && opStack.top() != '(') {
        out += opStack.top();
        out += ' ';
        opStack.pop();
      }
      if (!opStack.empty()) opStack.pop(); 
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(ch)) {
        out += opStack.top();
        out += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }
  }

  while (!opStack.empty()) {
    out += opStack.top();
    out += ' ';
    opStack.pop();
  }

  return out;
}

int eval(const std::string& post) {
  std::stack<int> valStack;

  for (size_t i = 0; i < post.length(); ++i) {
    char ch = post[i];

    if (std::isdigit(ch)) {
      int num = 0;
      while (i < post.length() && std::isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        ++i;
      }
      valStack.push(num);
      --i;
    } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
      if (valStack.size() < 2) throw std::runtime_error("Недостаточно операндов");

      int b = valStack.top(); valStack.pop();
      int a = valStack.top(); valStack.pop();

      switch (ch) {
        case '+': valStack.push(a + b); break;
        case '-': valStack.push(a - b); break;
        case '*': valStack.push(a * b); break;
        case '/': valStack.push(a / b); break;
      }
    }
  }

  if (valStack.size() != 1) throw std::runtime_error("Некорректное выражение");
  return valStack.top();
}
