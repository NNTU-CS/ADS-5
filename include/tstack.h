// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    int top;
    T* stack;

 public:
    TStack() : top(-1), stack(new T(size)) {}
    char Top(void) {
        if (IsEmpty()) throw std::string("Stack is EMPTY!");
        else
            return stack[top];
    }
    void Push(T value) {
        if (top == size - 1) {
            throw std::string("Stack is FULL!");
        } else {
            top++;
            stack[top] = value;
        }
    }
    const T& Pop() {
        if (IsEmpty()) {
            throw std::string("Stack is EMPTY!");
        }
        top--;
        return stack[top + 1];
    }
    bool IsEmpty() {
        if (top == -1) return true;
        else
            return false;
    }
};

#endif  // INCLUDE_TSTACK_H_
