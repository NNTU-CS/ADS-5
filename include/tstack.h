// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T el[size];
    int indx;

public:
    TStack() : indx(-1) {}

    void push(const T& value) {
        if (indx >= size - 1) {
            throw std::overflow_error("Stack overflow");
        }
        el[++indx] = value;
    }

    T pop() {
        if (indx < 0) {
            throw std::underflow_error("Stack underflow");
        }
        return el[indx--];
    }

    T top() const {
        if (indx < 0) {
            throw std::underflow_error("Stack is empty");
        }
        return el[indx];
    }

    bool isEmpty() const {
        return indx == -1;
    }

    int getSize() const {
        return indx + 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
