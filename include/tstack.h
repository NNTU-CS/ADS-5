// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, size_t N>
class TStack {
private:
    T arr[N];
    int top = -1;
public:
    bool isEmpty() const {
        return top == -1;
    }
    void push(const T& value) {
        if (top < static_cast<int>(N) - 1) {
            arr[++top] = value;
        } else {
            throw "Stack overflow";
        }
    }
    void pop() {
        if (!isEmpty()) {
            --top;
        } else {
            throw "Stack underflow";
        }
    }
    T get() const {
        if (!isEmpty()) {
            return arr[top];
        } else {
            throw "Stack is empty";
        }
    }
    size_t size() const {
        return top + 1;
    }
};
#endif
    return top == -1;
  }
};
#endif
