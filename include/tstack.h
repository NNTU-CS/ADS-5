#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template<typename T, int size>
class TStack {
    static const int Ks = size;
    T data[Ks];
    int top;

 public :
    TStack() : top(0) {
    }

    void push(const T &item) {
        if (top <= size - 1)
            data[top++] = item;
        else
            throw std::string(" This is full.");
    }

    T pop() {
        if (top > 0)
            return data[--top];
        else
            throw std::string(" Oh no, it is empty.");
    }

    bool isEmpty() {
        return top == 0;
    }

    T get() {
        if (!isEmpty())
            return data[top - 1];
        else
            throw std::string("Empty");
    }
};
#endif  // INCLUDE_TSTACK_H_
  69 changes: 65 additions & 4 deletions69  
src/alg.cpp
Viewed
@@ -4,11 +4,72 @@
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
  // добавьте код
  return std::string("");
    TStack<char, 100> stack1;
    std::string exit;
    for (char i : inf) {
        if (i == '(') {
            stack1.push(i);
        } else if (i >= '0' && i <= '9') {
            exit += i;
            exit += ' ';
        } else if (i == ')') {
            while (stack1.get() != '(' && !stack1.isEmpty()) {
                exit += stack1.pop();
                exit += ' ';
            }
            if (stack1.get() == '(')
                stack1.pop();
        } else if (i == '+' || i == '-' || i == '*' || i == '/') {
            while (!stack1.isEmpty() && (stack1.get() == '*' ||
                stack1.get() == '/' || (i == '+' || i == '-') &&
                (stack1.get() == '+' || stack1.get() == '-'))) {
                exit += stack1.pop();
                exit += ' ';
            }
            stack1.push(i);
        }
    }
    while (!stack1.isEmpty()) {
        exit += stack1.pop();
        exit += ' ';
    }
    exit.pop_back();
    return exit;
}

int eval(std::string pref) {
  // добавьте код
  return 0;
    TStack<int, 100> stack2;
    std::string sTemp;
    for (char i : pref) {
        if ((i >= '0' && i <= '9')) {
            sTemp += i;
        } else if (i == ' ' && !sTemp.empty()) {
            stack2.push(std::stoi(sTemp));
            sTemp.clear();
        } else if (i == '+' || i == '-' || i == '*' || i == '/') {
            switch (i) {
                case '*': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() * cTemp);
                    break;
                }
                case '/': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() / cTemp);
                    break;
                }
                case '+': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() + cTemp);
                    break;
                }
                case '-': {
                    int cTemp = stack2.pop();
                    stack2.push(stack2.pop() - cTemp);
                    break;
                }
            }
        }
    }
    return stack2.pop();
}
#endif  // INCLUDE_TSTACK_H_
