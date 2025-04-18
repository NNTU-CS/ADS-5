// Copyright 2025 NNTU-CS
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "tstack.h"

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
std::stringstream ss(post);
std::string token;
while (ss >> token) {
if (isdigit(token[0])) {
stack.push(std::stoi(token));
} else {
int right = stack.pop();
int left = stack.pop();
switch (token[0]) {
case '+': stack.push(left + right); break;
case '-': stack.push(left - right); break;
case '*': stack.push(left * right); break;
case '/': stack.push(left / right); break;
}
}
}
return stack.pop();
}
