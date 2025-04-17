// Copyright 2025 NNTU-CS
#include <cctype>
#include <map>
#include <string>

template <typename ElementType, int Capacity>
class Stack {
 private:
    ElementType data[Capacity];
    int current_position;

 public:
    Stack() : current_position(-1) {
        for (int i = 0; i < Capacity; ++i) {
            data[i] = ElementType();
        }
    }

    void push(const ElementType& value) {
        if (current_position < Capacity - 1) {
            data[++current_position] = value;
        }
    }

    ElementType pop() {
        if (current_position >= 0) {
            return data[current_position--];
        }
        return ElementType();
    }

    ElementType peek() const {
        if (current_position >= 0) {
            return data[current_position];
        }
        return ElementType();
    }

    bool is_empty() const {
        return current_position == -1;
    }
};

std::string infx2pstfx(const std::string& input_expr) {
    Stack<char, 100> operator_stack;
    std::string output_expr;
    std::map<char, int> precedence = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
    };

    for (size_t pos = 0; pos < input_expr.size(); ++pos) {
        char current_char = input_expr[pos];

        if (isdigit(current_char)) {
            while (pos < input_expr.size() && isdigit(input_expr[pos])) {
                output_expr += input_expr[pos++];
            }
            output_expr += ' ';
            --pos;
        } else if (current_char == '(') {
            operator_stack.push(current_char);
        } else if (current_char == ')') {
            while (!operator_stack.is_empty() && operator_stack.peek() != '(') {
                output_expr += operator_stack.pop();
                output_expr += ' ';
            }
            operator_stack.pop();  // Удаление '('
        } else if (precedence.count(current_char)) {
            while (!operator_stack.is_empty() && 
                   operator_stack.peek() != '(' &&
                   precedence[operator_stack.peek()] >= precedence[current_char]) {
                output_expr += operator_stack.pop();
                output_expr += ' ';
            }
            operator_stack.push(current_char);
        }
    }

    while (!operator_stack.is_empty()) {
        output_expr += operator_stack.pop();
        output_expr += ' ';
    }

    if (!output_expr.empty() && output_expr.back() == ' ') {
        output_expr.pop_back();
    }

    return output_expr;
}

int eval(const std::string& postfix_expr) {
    Stack<int, 100> computation_stack;
    std::string number_buffer;

    for (char current_char : postfix_expr) {
        if (isdigit(current_char)) {
            number_buffer += current_char;
        } else if (current_char == ' ' && !number_buffer.empty()) {
            computation_stack.push(std::stoi(number_buffer));
            number_buffer.clear();
        } else if (current_char == '+' || current_char == '-' || 
                   current_char == '*' || current_char == '/') {
            int right_operand = computation_stack.pop();
            int left_operand = computation_stack.pop();
            switch (current_char) {
                case '+':
                    computation_stack.push(left_operand + right_operand);
                    break;
                case '-':
                    computation_stack.push(left_operand - right_operand);
                    break;
                case '*':
                    computation_stack.push(left_operand * right_operand);
                    break;
                case '/':
                    computation_stack.push(left_operand / right_operand);
                    break;
            }
        }
    }

    return computation_stack.pop();
}
