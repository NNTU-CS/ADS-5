// Copyright 2025 NNTU-CS
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include "tstack.h"

int get_operator_priority(char oper) {
    switch (oper) {
    case '+':
    case '*':
    case '-': return 1;
    case '/': return 2;
    default: return 0;
    }
}


std::string infx2pstfx(const std::string& inf) {
    std::string result;
    CustomStack<char, 128> operator_stack;

    for (size_t idx = 0; idx < inf.size(); ++idx) {
        char curr_char = inf[idx];
        if (curr_char == ' ') {
            continue;
        }
        if (std::isdigit(curr_char)) {
            while (idx < inf.size() && std::isdigit(inf[idx])) {
                result += inf[idx++];
            }
            --idx;
            result += ' ';
        } else if (curr_char == '(') {
            operator_stack.add_item(curr_char);
        } else if (curr_char == ')') {
            while (!operator_stack.is_empty() && operator_stack.peek() != '(') {
                result += operator_stack.peek();
                result += ' ';
                operator_stack.remove_item();
            }
            if (!operator_stack.is_empty() && operator_stack.peek() == '(') {
                operator_stack.remove_item();
            } else {
                throw std::string("not correct");
            }
        } else if (curr_char == '+' || curr_char == '-' || curr_char == '*' || curr_char == '/') {
            while (!operator_stack.is_empty() &&
                   get_operator_priority(operator_stack.peek()) >= get_operator_priority(curr_char)) {
                result += operator_stack.peek();
                result += ' ';
                operator_stack.remove_item();
            }
            operator_stack.add_item(curr_char);
        } else {
            throw std::string("invalid symbol" + std::string(1, curr_char));
        }
    }

    while (!operator_stack.is_empty()) {
        if (operator_stack.peek() == '(' || operator_stack.peek() == ')') {
            throw std::string("not correct");
        }
        result += operator_stack.peek();
        result += ' ';
        operator_stack.remove_item();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}


int eval(const std::string& post) {
    CustomStack<int, 128> number_stack;
    std::istringstream stream(post);
    std::string token;

    while (stream >> token) {
        if (std::isdigit(token[0])) {
            int number = std::stoi(token);
            number_stack.add_item(number);
        } else if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            if (number_stack.is_empty()) {
                throw std::string("not enough of operands");
            }
            int second_operand = number_stack.peek();
            number_stack.remove_item();
            if (number_stack.is_empty()) {
                throw std::string("not enough of operands");
            }
            int first_operand = number_stack.peek();
            number_stack.remove_item();
            int calculated_result = 0;
            switch (token[0]) {
            case '+': calculated_result = first_operand + second_operand; break;
            case '*': calculated_result = first_operand * second_operand; break;
            case '-': calculated_result = first_operand - second_operand; break;
            case '/':
                if (second_operand == 0) {
                    throw std::string("division by zero");
                }
                calculated_result = first_operand / second_operand;
                break;
            default:
                throw std::string("not correct operation");
            }
            number_stack.add_item(calculated_result);
        } else {
            throw std::string("not correct symbol" );
        }
    }

    if (number_stack.is_empty()) {
        throw std::string("stack is empty");
    }
    int final_result = number_stack.peek();
    number_stack.remove_item();
    if (!number_stack.is_empty()) {
        throw std::string("not correct");
    }

    return final_result;
}
