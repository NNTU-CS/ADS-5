// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    static const int SSize = size;
    T data[SSize];
    int top;

 public:
    TStack() : top(0) {}
    void push(const T &item) {
        if (top <= size - 1)
            data[top++] = item;
    }
    T pop() {
        if (top > 0)
            return data[--top];
        else
            throw 0;
    }
    bool isEmpty() {
        return top == 0;
    }
    T get() {
        if (!isEmpty())
            return data[top - 1];
        else
            throw 0;
    }
};
#endif  // INCLUDE_TSTACK_H_
