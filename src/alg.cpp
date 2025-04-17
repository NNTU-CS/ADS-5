// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

template <typename T, int size>
class TStack {
private:
    T arr[size];
    int top;

public:
    TStack() {
        top = -1;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == size - 1;
    }

    void push(const T& value) {
        if (isFull()) {
            throw std::string("Stack is full!");
        }
        arr[++top] = value;
    }

    T pop() {
        if (isEmpty()) {
            throw std::string("Stack is empty!");
        }
        return arr[top--];
    }

    T get() const {
        if (isEmpty()) {
            throw std::string("Stack is empty!");
        }
        return arr[top];
    }
};

int priority(char sym) {
    switch (sym) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
        default : return -1;
    };
}

std::string infx2pstfx(const std::string& inf) {
  std::string postfix = "";
    TStack<char, 100> transStack;

    for (int i = 0; i < inf.length(); ++i) {
        char cur = inf[i];

        if (isdigit(cur)) {
            std::string num;
            while (i < inf.length() && isdigit(inf[i])) {
                num += inf[i];
                i++;
            }
            i--;
            postfix += num + " ";
        } else if (cur == '(') {
            transStack.push(cur);
        } else if (cur == ')') {
            while (!transStack.isEmpty() && transStack.get() != '(') {
                postfix += transStack.pop();
                postfix += " ";
            }
            if (!transStack.isEmpty() && transStack.get() == '(') {
                transStack.pop();
            }
        } else if (cur == '+' || cur == '-' || cur == '*' || cur == '/') {
            while (!transStack.isEmpty() && priority(cur) <= priority(transStack.get())) {
                postfix += transStack.pop();
                postfix += " ";
            }
            transStack.push(cur);
        }
        else if (cur == ' ') {
            continue;
        }
    }

    while (!transStack.isEmpty()) {
        postfix += transStack.pop();
        postfix += " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;

}

int eval(const std::string& post) {
  TStack<int, 100> countStack; 
    std::string currentNumber;
    for (int i = 0; i < post.length(); ++i) {
        char curSym = post[i];

        if (isdigit(curSym)) {
            currentNumber += curSym;
        } else if (curSym == ' ') {
            if (!currentNumber.empty()) {
                countStack.push(stoi(currentNumber));
                currentNumber.clear();
            }
        } else if (curSym == '+' || curSym == '-' || curSym == '*' || curSym == '/') {
            if (countStack.isEmpty()) {
                return 0; 
            }
            int operand2 = countStack.pop();
            if (countStack.isEmpty()) {
                return 0;
            }
            int operand1 = countStack.pop();

            int result;
            switch (curSym) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                         return 0;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    return 0;
            }
            countStack.push(result);
        }
    }

    if (countStack.isEmpty()) {
        return 0;
    }

    return countStack.pop();
}
