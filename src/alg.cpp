// Copyright 2021 NNTU-CS
#include <cctype>
#include <map>
#include <sstream>
#include <string>

#include "tstack.h"

int grabNum(int *index, std::string str) {
    int ret = 0;
    while (*index < str.size() && isdigit(str[*index])) {
        ret *= 10;
        ret += str[*index] - '0';
        index++;
    }
    return ret;
}

int getPrecedence(char c) {
    static std::string alphabet("-+/*^");
    return alphabet.find(c);
}

std::string infx2pstfx(std::string inf) {
    std::stringstream ss;
    TStack<char, 100> stack;

    for (int i = 0; i < inf.size(); i++) {
        if (isdigit(inf[i])) {
            ss << " " << grabNum(&i, inf);
            continue;
        }

        if ('(' == inf[i]) {
            stack.push(inf[i]);
            continue;
        }

        if (')' == inf[i]) {
            while (stack.get() != '(') ss << " " << stack.pop();
            stack.pop();
            continue;
        }

        if (getPrecedence(inf[i]) == std::string::npos) continue;

        while (!stack.isEmpty() && (stack.get() != '(') &&
               (getPrecedence(stack.get()) >= getPrecedence(inf[i])))
            ss << " " << stack.pop();

        stack.push(inf[i]);
    }

    while (!stack.isEmpty()) ss << " " << stack.pop();

    ss.seekg(1);
    return std::string(std::istreambuf_iterator<char>(ss), {});
}

int eval(std::string pref) {
    TStack<int, 100> stack;

    for (int i = 0; i < pref.size(); i++) {
        if (isdigit(pref[i])) {
            stack.push(grabNum(&i, pref));
            continue;
        }
        int left, right;
        switch (pref[i]) {
            case '+':
                stack.push(stack.pop() + stack.pop());
                break;
            case '-':
                right = stack.pop();
                left = stack.pop();
                stack.push(left - right);
                break;
            case '*':
                stack.push(stack.pop() * stack.pop());
                break;
            case '/':
                right = stack.pop();
                left = stack.pop();
                stack.push(left / right);
                break;
        }
    }
    return stack.pop();
}
