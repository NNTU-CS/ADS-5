// Copyright 2025 NNTU-CS
#include "tstack.h"
#include <iostream>
#include <string>

std::string infx2pstfx(std::string inf);
int eval(const std::string& pref);

int main() {
    std::string inf = "8*(3+7)/2";
    std::string pref = infx2pstfx(inf);
    std::cout << infx2pstfx(inf) << std::endl;
    std::cout << eval(pref) << std::endl;
    return 0;
}

std::string infx2pstfx(std::string inf) {
    SStack<char, 100> stack1;
    std::string newstring = "";
    for (int i = 0; i < inf.length() + 1; i++) {
        char operat1 = inf[i];
        int prior1 = 0;
        switch (operat1) {
            case '(': prior1 = 0; break;
            case ')': prior1 = 1; break;
            case '+': case '-': prior1 = 2; break;
            case '*': case '/': prior1 = 3; break;
        }

        int prior2 = 0;
        if (!stack1.isEmpty()) {
            char operat2 = stack1.get();
            switch (operat2) {
                case '(': prior2 = 0; break;
                case ')': prior2 = 1; break;
                case '+': case '-': prior2 = 2; break;
                case '*': case '/': prior2 = 3; break;
            }
        }

        if (inf[i] >= '0' && inf[i] <= '9') {
            newstring += inf[i];
            newstring += ' ';
        } else if ((inf[i] >= '(' && inf[i] <= '/') && inf[i] != ')') {
            if (inf[i] == '(') {
                stack1.push('(');
            } else if (prior1 > prior2 || stack1.isEmpty()) {
                stack1.push(inf[i]);
            } else {
                while (prior1 <= prior2) {
                    char operat2 = stack1.get();
                    prior2 = 0;
                    switch (operat2) {
                        case '(': prior2 = 0; break;
                        case ')': prior2 = 1; break;
                        case '+': case '-': prior2 = 2; break;
                        case '*': case '/': prior2 = 3; break;
                    }

                    if (stack1.get() != '(') {
                        newstring += stack1.get();
                        newstring += ' ';
                        stack1.pop();
                    }

                    if (!stack1.isEmpty()) {
                        char topOper = stack1.get();
                        prior1 = 0;
                        switch (topOper) {
                            case '(': prior1 = 0; break;
                            case ')': prior1 = 1; break;
                            case '+': case '-': prior1 = 2; break;
                            case '*': case '/': prior1 = 3; break;
                        }
                        if (topOper == '(') break;
                    } else {
                        break;
                    }
                }
                stack1.push(inf[i]);
            }
        } else if (inf[i] == ')') {
            while (stack1.get() != '(') {
                if (stack1.isEmpty()) break;
                newstring += stack1.get();
                newstring += ' ';
                stack1.pop();
            }
            stack1.pop();
        }

        if (inf[i] == '\0') {
            while (!stack1.isEmpty()) {
                newstring += stack1.get();
                newstring += ' ';
                stack1.pop();
            }
        }
    }
    newstring.pop_back();
    return newstring;
}

int eval(const std::string& pref) {
    SStack<int, 100> stack2;
    std::string timeline = "";
    for (int i = 0; i < pref.length() + 1; i++) {
        if (pref[i] >= '0' && pref[i] <= '9') {
            timeline += pref[i];
        } else if (pref[i] == ' ' && timeline != "") {
            int num = std::stoi(timeline);
            stack2.push(num);
            timeline = "";
        } else if (pref[i] >= '(' && pref[i] <= '/') {
            char s = pref[i];
            int num1 = stack2.get();
            stack2.pop();
            int num2 = stack2.get();
            stack2.pop();
            int res = 0;
            switch (s) {
                case '+': res = num1 + num2; break;
                case '-': res = num2 - num1; break;
                case '*': res = num2 * num1; break;
                case '/': res = num2 / num1; break;
            }
            stack2.push(res);
        }

        if (pref[i] == '\0') {
            return stack2.get();
        }
    }
    return 0;
}
