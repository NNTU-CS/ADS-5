// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stackBuffer;
    std::string result = "";
    int amountOfBrackets = 0;
    for (int i = 0; i < inf.size(); i++) {
        if (inf[i] == '(') {
            stackBuffer.push('(');
            amountOfBrackets++;
        } else if (inf[i] == ')') {
            char topChar = stackBuffer.pop();
            while (topChar != '(') {
                result += ' ';
                result += topChar;
                topChar = stackBuffer.pop();
            }
            amountOfBrackets--;
        } else if (
            inf[i] == '0' ||
            inf[i] == '1' ||
            inf[i] == '2' ||
            inf[i] == '3' ||
            inf[i] == '4' ||
            inf[i] == '5' ||
            inf[i] == '6' ||
            inf[i] == '7' ||
            inf[i] == '8' ||
            inf[i] == '9') {
            result += inf[i];
        } else if (inf[i] == '+' || inf[i] == '-') {
            char bot;
            try {
                bot = stackBuffer.seeBottom();
            } catch (std::exception) {
                bot = ' ';
            }
            if (amountOfBrackets > 0) {
            } else if (bot == '*' || bot == '/') {
                while (!stackBuffer.isEmpty()) {
                    result += ' ';
                    result += stackBuffer.pop();
                }
            }

            result += ' ';
            stackBuffer.push(inf[i]);
        } else if (inf[i] == '*' || inf[i] == '/') {
            char bot;
            try {
                bot = stackBuffer.seeBottom();
            } catch (std::exception) {
                bot = ' ';
            }
            if (bot == '*' || bot == '/') {
                while (!stackBuffer.isEmpty()) {
                    result += ' ';
                    result += stackBuffer.pop();
                }
            }
            result += ' ';
            stackBuffer.push(inf[i]);
        }
    }
    while (!stackBuffer.isEmpty()) {
        result += ' ';
        result += stackBuffer.pop();
    }
    return result;
}

int eval(std::string pref) {
    TStack<int, 100> stack;
    for (int i = 0; i < pref.size(); i++) {
        if (pref[i] == '0' ||
            pref[i] == '1' ||
            pref[i] == '2' ||
            pref[i] == '3' ||
            pref[i] == '4' ||
            pref[i] == '5' ||
            pref[i] == '6' ||
            pref[i] == '7' ||
            pref[i] == '8' ||
            pref[i] == '9') {
            int a = (pref[i] - '0');
            i++;
            while (
                pref[i] == '0' ||
                pref[i] == '1' ||
                pref[i] == '2' ||
                pref[i] == '3' ||
                pref[i] == '4' ||
                pref[i] == '5' ||
                pref[i] == '6' ||
                pref[i] == '7' ||
                pref[i] == '8' ||
                pref[i] == '9'
                ) {
                a = a * 10 + (pref[i] - '0');
                i++;
            }
            i--;
            stack.push(a);
        } else {
            int a, b;
            switch (pref[i]) {
            case '+':
                a = stack.pop();
                b = stack.pop();
                stack.push(b + a);
                break;
            case '-':
                a = stack.pop();
                b = stack.pop();
                stack.push(b - a);
                break;
            case '*':
                a = stack.pop();
                b = stack.pop();
                stack.push(b * a);
                break;
            case '/':
                a = stack.pop();
                b = stack.pop();
                stack.push(b / a);
                break;
            }
        }
    }
    return stack.pop();
}
