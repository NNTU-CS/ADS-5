// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

bool isOperator(char c) { return c == '+' || c == '-' ||
c == '*' || c == '/'; }
int Oper(int a, int b, char op) {
switch (op) {
case '+':
return a + b;
case '-':
return a - b;
case '*':
return a * b;
case '/':
return a / b;
}
return 0;
}
static int priority(char op) {
if (op == '+' || op == '-') return 1;
if (op == '*' || op == '/') return 2;
return 0;
}

std::string infx2pstfx(const std::string& inf) {
TStack<char, 100> stack;
std::stringstream res;
bool first = true;
for (size_t i = 0; i < inf.size(); ++i) {
char c = inf[i];
if (isspace(c)) {
continue;
}
if (isdigit(c)) {
if (!first) {
res << ' ';
}
res << c;
first = false;
} else {
if (c == '(') {
stack.push(c);
} else if (c == ')') {
while (!stack.isEmpty() && stack.peek() != '(') {
res << ' ' << stack.pop();
}
stack.pop();
} else {
while (!stack.isEmpty() && stack.peek() != '(' &&
priority(stack.peek()) >= priority(c)) {
res << ' ' << stack.pop();
}
stack.push(c);
}
}
}
while (!stack.isEmpty()) {
res << ' ' << stack.pop();
}
return res.str();
}

int eval(const std::string& post) {
TStack<int, 100> stack;
for (size_t i = 0; i < post.length(); i++) {
if (isspace(post[i])) continue;
if (isdigit(post[i])) {
stack.push(post[i] - '0');
} else if (isOperator(post[i])) {
int b = stack.pop();
int a = stack.pop();
stack.push(Oper(a, b, post[i]));
}
}
return stack.pop();
}
