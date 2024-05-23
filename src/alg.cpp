// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "alg.h"
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string end;
    for (int i = 0; i < inf.length(); i++) {
        if (inf[i] == '(') {
            stack1.push(inf[i]);
        } else if ((inf[i] >= '0') && (inf[i] <= '9')) {
            end += inf[i];
            end += ' ';
        } else if (inf[i] == ')') {
            while ((!stack1.isEmpty()) && (stack1.get() != '(')) {
                end += stack1.pop();
                end += ' ';
            }
            if (stack1.get() == '(') {
                stack1.pop();
            }
        } else if (inf[i] == '+' || inf[i] == '-') {
            if (!stack1.isEmpty()) {
                switch (stack1.get()) {
                    case '*': {
                        end += '*';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                    case '/': {
                        end += '/';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                    case '+': {
                        end += '+';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                    case '-': {
                        end += '-';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                }
                stack1.push(inf[i]);
            } else {
                stack1.push(inf[i]);
            }
        } else if (inf[i] == '*' || inf[i] == '/') {
            if (!stack1.isEmpty()) {
                switch (stack1.get()) {
                    case '*': {
                        end += '*';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                    case '/': {
                        end += '/';
                        end += ' ';
                        stack1.pop();
                        break;
                    }
                }
                stack1.push(inf[i]);
            } else {
                stack1.push(inf[i]);
            }
        }
    }
    if (!stack1.isEmpty()) {
        while (!stack1.isEmpty()) {
            end += stack1.pop();
            end += ' ';
        }
    }
    std::string end2;
    for (int i = 0; i < (end.length() - 1); i++) {
        end2 += end[i];
    }
    return end2;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        if ((pref[i] >= '0') && (pref[i] <= '9')) {
            stack2.push(pref[i] - '0');
        } else if (pref[i] != ' ' || (pref[i] < '0') && (pref[i] > '9')) {
            int znak1 = stack2.pop();
            int znak2 = stack2.pop();
            switch (pref[i]) {
            case '+':
                stack2.push(znak2 + znak1);
                break;
            case '-':
                stack2.push(znak2 - znak1);
                break;
            case '*':
                stack2.push(znak2 * znak1);
                break;
            case '/':
                stack2.push(znak2 / znak1);
                break;
            }
        }
    }
    return stack2.get();
}
