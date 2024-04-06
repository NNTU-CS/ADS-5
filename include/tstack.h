// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* _stack;
    int _max_size;
    int top;

 public:
    TStack() : top(-1) {
        _stack = new T[size];
        _max_size = size;
        top = -1;
    }

    ~TStack() {
        delete[] _stack;
    }

    void push(T value) {
        top++;
        if (top >= _max_size) {
            return;
        }
        _stack[top] = value;
    }
    T get() {
        return _stack[top];
    }
    T pop() {
        return top--;
    }
    bool isEmpty() const {
        return top == -1;
    }
};
#endif  // INCLUDE_TSTACK_H_
