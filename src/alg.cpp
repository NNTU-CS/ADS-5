// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

template <class T, int size>
class TStack {
private:
  T arr[size];
  int top;
public:
  TStack() : top(-1) {
    
  }
  void push(T item) {
    arr[++top] = item;
  }
  T pop() {
        return arr[top--];
    }
    T get() {
        return arr[top];
    }
    bool isEmpty() {
        return top == -1;
    }
};

TStack<char, 100> stack1;
TStack<int, 100> stack2;

std::map<char, int> p {
    { '(', 0 }, { ')', 1 }, { '+', 2 }, { '-', 2 }, { '*', 3 }, { '/', 3 }
};

std::string infx2pstfx(std::string inf) {
    std::string strochka = "";
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] >= '0' && inf[i] <= '9') {
            strochka += inf[i];
            strochka += ' ';
        } else {
            if (stack1.isEmpty() == 1 || inf[i] == '(' || p[inf[i]] > p[stack1.get()]) {
                stack1.push(inf[i]);
            } else if (inf[i] == ')') {
                while (stack1.get() != '(') {
                    strochka = strochka + stack1.pop() + ' ';
                }
                if (stack1.get() == '(') {
                    stack1.pop();
                }
            } else if (p[inf[i]] <= p[stack1.get()]) {
                char perem = stack1.pop();
                strochka = strochka + perem + ' ';
                stack1.push(inf[i]);
            }
        }
    }
    while (!stack1.isEmpty()) {
        strochka = strochka + stack1.pop() + ' ';
    }
    return strochka;
}

int eval(std::string pref) {
    std::string strochka1;
    char perem;
    for (char i : pref) {
        if (i >= '0' && i <= '9') {
            strochka1 += i;
        } else {
            switch (i) {
                case '*':
                    perem = stack2.pop();
                    stack2.push(stack2.pop() * perem);
                    break;
                case '/':
                    perem = stack2.pop();
                    stack2.push(stack2.pop() / perem);
                    break;
                case '+':
                    perem = stack2.pop();
                    stack2.push(stack2.pop() + perem);
                    break;
                case '-':
                    perem = stack2.pop();
                    stack2.push(stack2.pop() - perem);
                    break;
            }
        }
    }
    return stack2.pop();
}
