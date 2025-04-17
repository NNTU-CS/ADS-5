// Copyright 2025 NNTU-CS
#include "tstack.h"
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

int prioritet(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infx2pstfx(const string& inf) {
    TStack<char, 100> op_stack;
    string output;
    size_t i = 0;
    while (i < inf.size()) {
        char c = inf[i];
        if (isdigit(c)) {
            string number;
            while (i < inf.size() && isdigit(inf[i])) {
                number += inf[i];
                i++;
            }
            output += number + " ";
        }
        else if (c == '(') {
            op_stack.Push(c);
            i++;
        }
        else if (c == ')') {
            while (!op_stack.IsEmpty() && op_stack.Top() != '(') {
                output += op_stack.Pop() + " ";
            }
            op_stack.Pop();
            i++;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!op_stack.IsEmpty() && op_stack.Top() != '(' && prioritet(c) <= prioritet(op_stack.Top())) {
                output += op_stack.Pop() + " ";
            }
            op_stack.Push(c);
            i++;
        }
        else {
            i++;
        }
    }
    while (!op_stack.IsEmpty()) {
        output += op_stack.Pop() + " ";
    }
    if (!output.empty()) {
        output.pop_back();
    }
    return output;
}

int eval(const std::string& pref) {
  // добавьте код
  return 0;
}
