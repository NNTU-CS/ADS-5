// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int SIZE>
class TStack {
 private:
    T *data = new T[100];
    int top = 0, size = 100;

 public:
    TStack() {
        data = new T[SIZE];
        size = SIZE;
        top = 0;
    }
    ~TStack() { delete[] data; }
    void push(T item) {
        data[top] = item;
        top++;
    }
    T pop() {
        if (top == 0) {
            throw "Stack is empty!";
        } else {
            top -= 1;
            return data[top];
        }
    }
    T check() {
        if (top == 0) {
            throw "Stack is empty!";
        } else {
            return data[top - 1];
        }
    }
    bool isempty() {
        if (top == 0) {
            return true;
        } else {
            return false;
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
