// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string result;
TStack<char, 100> opStack;
std::stringstream ss(inf);
std::string token;
std::map<char, int> precedence;
precedence['+'] = 1;
precedence['-'] = 1;
precedence['*'] = 2;
precedence['/'] = 2;
while (ss >> token) {
if (isdigit(token[0])) {
result += token + " ";
}
else if (token == "(") {
opStack.push(token[0]);
}
else if (token == ")") {
while (!opStack.empty() && opStack.top() != '(') {
result += opStack.top();
result += " ";
opStack.pop();
}
opStack.pop();
}
else {
while (!opStack.empty() && precedence[opStack.top()] >= precedence[token[0]]) {
result += opStack.top();
result += " ";
opStack.pop();
}
opStack.push(token[0]);
}
}
while (!opStack.empty()) {
result += opStack.top();
result += " ";
opStack.pop();
}
result.pop_back(); 
return result;
}

int eval(const std::string& pref) {
TStack<int, 100> operandStack;
std::stringstream ss(post);
std::string token;
while (ss >> token) {
if (isdigit(token[0])) {
int num = 0;
for (char c : token) {
num = num * 10 + (c - '0');
}
operandStack.push(num);
} else {
int operand2 = operandStack.top();
operandStack.pop();
int operand1 = operandStack.top();
operandStack.pop();
if (token == "+") {
operandStack.push(operand1 + operand2);
}
else if (token == "-") {
operandStack.push(operand1 - operand2);
}
else if (token == "*") {
operandStack.push(operand1 * operand2);
}
else if (token == "/") {
operandStack.push(operand1 / operand2);
}
}
}
return operandStack.top();
}
