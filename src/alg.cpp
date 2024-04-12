// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priorityOperations(char operSymb) {
    switch (operSymb) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
            return 2;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
        default:
            return -1;
    }
}

bool isOperation(char nowSymb) {
    return (nowSymb == '+' || nowSymb == '-' ||
    nowSymb == '*' || nowSymb == '/');
}

std::string infx2pstfx(std::string inf) {
    std::string pstfxString = "";
    TStack<char, 100> stack1;
    for (int i = 0; i < inf.length(); i++) {
        char currentElement = inf[i];
        if (currentElement >= '0' && currentElement <= '9') {
            pstfxString += currentElement;
            pstfxString += ' ';
        } else {
            if (stack1.isEmpty() == 1 || currentElement == '(' ||
            priorityOperations(currentElement) >
            priorityOperations(stack1.get())) {
                stack1.push(currentElement);
            } else if (priorityOperations(currentElement) <=
            priorityOperations(stack1.get())) {
                if (isOperation(currentElement)) {
                    pstfxString = pstfxString + stack1.pop();
                    pstfxString = pstfxString + ' ';
                    stack1.push(currentElement);
                }
            }
            if (currentElement == ')') {
                while (stack1.get() != '(') {
                    pstfxString = pstfxString + stack1.pop();
                    pstfxString = pstfxString + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            }
        }
    }
    while (stack1.isEmpty() != 1) {
        pstfxString = pstfxString + stack1.pop();
        if (stack1.isEmpty() != 1) {
            pstfxString += ' ';
        }
    }
    return pstfxString;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    std::string newNumber;
    char secondNum;
    for (char currentElement : pref) {
        if (currentElement >= '0' && currentElement <= '9') {
            newNumber += currentElement;
        } else if (!newNumber.empty() && currentElement == ' ') {
            stack2.push(std::stoi(newNumber));
            newNumber = "";
        } else {
            switch (currentElement) {
                case '+': {
                    secondNum = stack2.pop();
                    stack2.push(stack2.pop() + secondNum);
                    break;
                }
                case '-': {
                    secondNum = stack2.pop();
                    stack2.push(stack2.pop() - secondNum);
                    break;
                }
                case '*': {
                    secondNum = stack2.pop();
                    stack2.push(stack2.pop() * secondNum);
                    break;
                }
                case '/': {
                    secondNum = stack2.pop();
                    stack2.push(stack2.pop() / secondNum);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
