// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, const int size>
class TStack {
 private:
    T* data = new T[size];
    int top;

 public:
    TStack() : top(0) {}
    void push(const T& item) {
        if (top <= size - 1) data[top++] = item;
        else
            throw std::string("Full");
    }
    T pop() {
        if (top > 0) return data[--top];
        else
            throw std::string("Empty");
    }

    int getTop() {
        return top;
    }
    int getPriority() {
        T f = data[top - 1];
        int pr = -1;
        switch (f) {
        case '(': pr = 0; break;
        case ')': pr = 1; break;
        case '+': pr = 2; break;
        case '-': pr = 2; break;
        case '*': pr = 3; break;
        case '/': pr = 3; break;
        }
        return pr;
    }
};

#endif  // INCLUDE_TSTACK_H_
