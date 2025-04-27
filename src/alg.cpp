// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int znak(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    std::string output;
    std::string operators;
    std::string t;
    size_t i = 0;

    while (i < inf.size()) {
        if (isspace(inf[i])) {
            i++;
            continue;
        }
        if (isdigit(inf[i])) {
            while (i < inf.size() && (isdigit(inf[i]))) {
                t += inf[i++];
            }
            output += t + " ";
            t.clear();
        } else if (inf[i] == '(') {
            operators += '(';
            i++;
        } else if (inf[i] == ')') {
            while (!operators.empty() && operators.back() != '(') {
                output += operators.back();
                output += " ";
                operators.pop_back();
            }
            if (!operators.empty()) {
                operators.pop_back();
            }
            i++;
        } else {
            while (!operators.empty() &&
            znak(operators.back()) >= znak(inf[i])) {
                output += operators.back();
                output += " ";
                operators.pop_back();
            }
            operators += inf[i++];
        }
    }

    while (!operators.empty()) {
        output += operators.back();
        output += " ";
        operators.pop_back();
    }
    output.pop_back();
    return output;
}

int eval(const std::string& post) {
    std::string values[100];
    int top = -1;
    size_t i = 0;

    while (i < post.size()) {
        if (isspace(post[i])) {
            i++;
            continue;
        }

        std::string t;

        if (isdigit(post[i])) {
            while (i < post.size() && (isdigit(post[i]))) {
                t += post[i++];
            }
            values[++top] = t;
        } else {
            int right = std::stoi(values[top--]);
            int left = std::stoi(values[top--]);
            switch (post[i]) {
                case ('+'):
                    values[++top] = std::to_string(left + right);
                    break;
                case ('-'):
                    values[++top] = std::to_string(left - right);
                    break;
                case ('*'):
                    values[++top] = std::to_string(left * right);
                    break;
                case ('/'):
                    values[++top] = std::to_string(left / right);
                    break;
            }
            i++;
        }
    }

    return std::stoi(values[top]);
}
