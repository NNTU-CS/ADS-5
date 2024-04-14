// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int alphabet(char c) {
    switch (c) {
    case('1'): return 1;
    case('2'): return 2;
    case('3'): return 3;
    case('4'): return 4;
    case('5'): return 5;
    case('6'): return 6;
    case('7'): return 7;
    case('8'): return 8;
    case('9'): return 9;
    case('0'): return 0;
    }
    return -1;
}

bool Cheching_for_a_Num(char a) {
    return (a >= '0' && a <= '9');
}

int get_operator_priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

int ifOperator(char c) {
    switch (c) {
    case('+'): return 1;
    case('-'): return 2;
    case('*'): return 3;
    case('/'): return 4;
    }
    return 0;
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> s;
    std::string result = "";
    for (int i = 0; i < inf.length(); i++) {
        char c = inf[i];
        if (Cheching_for_a_Num(c)) {
            result += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.isEmpty() && s.Get() != '(') {
                result += s.Get();
                s.Pop();
            }
            s.Pop();
        } else if (ifOperator(c)) {
            while (!s.isEmpty() && \
                get_operator_priority(s.Get()) >= get_operator_priority(c)) {
                result += s.Get();
                s.Pop();
            }
            s.push(c);
        }
    }
    while (!s.isEmpty()) {
        result += s.Get();
        s.Pop();
    }
    std::string end;
    for (int i = 0; i < result.length(); i++) {
        if (i < result.length() - 1) {
            end = end + result[i] + ' ';
        } else {
            end = end + result[i];
        }
    }
    return end;
}
int eval(std::string post) {
    TStack <int, 100> s;
    for (int i = 0; i < post.length(); i += 2) {
        char c = post[i];
        if (Cheching_for_a_Num(c)) {
            s.push(alphabet(c));
        } else {
            int temp2 = s.Get();
            s.Pop();
            int temp1 = s.Get();
            s.Pop();
            switch (c) {
            case '+':
                s.push(temp1 + temp2);
                break;
            case '-':
                s.push(temp1 - temp2);
                break;
            case '*':
                s.push(temp1 * temp2);
                break;
            case '/':
                s.push(temp1 / temp2);
                break;
            }
        }
    }
    return s.Get();
}
