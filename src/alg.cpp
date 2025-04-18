// Modified algorithm implementation
#include <string>
#include <cctype>
#include "tstack.h"

namespace {
    int determineOpPrecedence(char operation) {
        const std::pair<char, int> operators[] = {
            {'(', 0}, {')', 1}, {'+', 2}, 
            {'-', 2}, {'*', 3}, {'/', 3}
        };
        for (const auto& op : operators) {
            if (op.first == operation) {
                return op.second;
            }
        }
        return -1;
    }

    std::string formatOutputString(const std::string& str) {
        if (str.length() < 3) return str;
        int start = 2 - str.length() % 2;
        std::string result(str, 0, start);
        for (auto it = str.begin() + start; it != str.end(); ++it) {
            result += ' ';
            result += *it;
        }
        return result;
    }

    int performOperation(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    }
}

std::string infx2pstfx(std::string inputExpr) {
    std::string output;
    TStack<char, 100> opStack;
    
    for (char ch : inputExpr) {
        int precedence = determineOpPrecedence(ch);
        if (precedence == -1) {
            output += ch;
        } else {
            if (opStack.isEmpty() || precedence == 0 || 
                determineOpPrecedence(opStack.get()) < precedence) {
                opStack.push(ch);
            } else if (ch == ')') {
                while (!opStack.isEmpty() && 
                       determineOpPrecedence(opStack.get()) >= 1) {
                    output += opStack.get();
                    opStack.pop();
                }
                opStack.pop();
            } else {
                while (!opStack.isEmpty() && 
                       determineOpPrecedence(opStack.get()) >= precedence) {
                    output += opStack.get();
                    opStack.pop();
                }
                opStack.push(ch);
            }
        }
    }
    
    while (!opStack.isEmpty()) {
        output += opStack.get();
        opStack.pop();
    }
    
    return formatOutputString(output);
}

int eval(const std::string& postfixExpr) {
    TStack<int, 100> numStack;
    std::string currentNum;
    
    for (size_t i = 0; i < postfixExpr.size(); ++i) {
        char c = postfixExpr[i];
        if (determineOpPrecedence(c) == -1) {
            if (c == ' ') {
                if (!currentNum.empty()) {
                    numStack.push(std::stoi(currentNum));
                    currentNum.clear();
                }
            } else if (isdigit(c)) {
                currentNum += c;
            }
        } else {
            int b = numStack.get();
            numStack.pop();
            int a = numStack.get();
            numStack.pop();
            numStack.push(performOperation(a, b, c));
        }
    }
    
    return numStack.get();
}
