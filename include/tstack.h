// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T data[size];
    int top;
public:
    TStack() : top(-1) {}
    void push(const T& value) {
        if (top >= size - 1)
            throw std::overflow_error("Stack overflow");
        data[++top] = value;
    }
    void pop() {
        if (isEmpty())
            throw std::underflow_error("Stack underflow");
        --top;
    }
    T get() const {
        if (isEmpty())
            throw std::underflow_error("Stack underflow");
        return data[top];
    }
    bool isEmpty() const {
        return top == -1;
    }
    int count() const {
        return top + 1;
    }
};
};
#endif  // INCLUDE_TSTACK_H_
