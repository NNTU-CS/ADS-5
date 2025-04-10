// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
private:
    T data[size];
    int top;
public:
    TStack() : top(-1) {}
    bool isEmpty() const {
        return top == -1;
    }
    bool isFull() const {
        return top == size - 1;
    }
    void push(const T& value) {
        if (!isFull()) {
            data[++top] = value;
        }
    }
    T pop() {
        if (!isEmpty()) {
            return data[top--];
        }
        throw std::out_of_range("Stack is empty");
    }
    T peek() const {
        if (!isEmpty()) {
            return data[top];
        }
        throw std::out_of_range("Stack is empty");
    }
};
#endif // TSTACK_H
