// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string outputExpr;
    TStack<char, 100> opStack;
    std::map<char, int> precedence = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2} 
    }; 

    for (size_t i = 0; i < inf.size(); ++i) {
        char ch = inf[i];
        
        if (isdigit(ch)) {
            while (i < inf.size() && isdigit(inf[i])) {
                outputExpr += inf[i++];
            }
            outputExpr += ' ';
            i--;
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.isEmpty() && opStack.top() != '(') {
                outputExpr += opStack.top();
                outputExpr += ' ';
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.isEmpty() && opStack.top() != '(' && 
                   precedence[ch] <= precedence[opStack.top()]) {
                outputExpr += opStack.top();
                outputExpr += ' ';
                opStack.pop();
            }
            opStack.push(ch);
        }
    }

    while (!opStack.isEmpty()) {
        outputExpr += opStack.top();
        outputExpr += ' ';
        opStack.pop();
    }

    if (!outputExpr.empty() && outputExpr.back() == ' ') {
        outputExpr.pop_back();
    }

    return outputExpr;
}

int eval(const std::string& pref) {
    TStack<int, 100> numStack;

    for (size_t j = 0; j < pref.size(); ++j) {
        char symb = pref[j];
        
        if (isdigit(symb)) {
            int val = 0;
            while (j < pref.size() && isdigit(pref[j])) {
                val = val * 10 + (pref[j++] - '0');
            }
            numStack.push(val);
            j--;
        } else if (symb == ' ') {
            continue;
        } else {
            int rhs = numStack.top();
            numStack.pop();
            int lhs = numStack.top();
            numStack.pop();
            
            switch (symb) {
                case '+': numStack.push(lhs + rhs); break;
                case '-': numStack.push(lhs - rhs); break;
                case '*': numStack.push(lhs * rhs); break;
                case '/': numStack.push(lhs / rhs); break;
            }
        }
    }

    return numStack.top();
}
