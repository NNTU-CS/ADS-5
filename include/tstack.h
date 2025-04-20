// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
public:
    TStack() : top(-1) {}

    void push(const T& item) {
        if (top >= size - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data[++top] = item;
    }

    void pop() {
        if (top < 0) {
            throw std::underflow_error("Stack underflow");
        }
        --top;
    }

    T topItem() const {
        if (top < 0) {
            throw std::underflow_error("Stack is empty");
        }
        return data[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

private:
    T data[size];
    int top;
};

#endif
