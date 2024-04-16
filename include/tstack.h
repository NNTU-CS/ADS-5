// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
template <class T, int size>
class Stack {
private:
    T stack[size];
    int top;

public:
    Stack() : top(-1) {}

    bool isFull() {
        return top == size - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(T value) {
        if (!isFull()) {
            top++;
            stack[top] = value;
        } else {
            throw std::overflow_error("Stack is full");
        }
    }

    T pop() {
        if (!isEmpty()) {
            T value = stack[top];
            top--;
            return value;
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    T get() {
        if (!isEmpty()) {
            return stack[top];
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
