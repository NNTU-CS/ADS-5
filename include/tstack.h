// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* arr;
    int top;

 public:
    TStack() : top(-1) {
        arr = new T[size];
    }
    ~TStack() {
        delete[] arr;
        arr = nullptr;
    }
    bool isFull() const {
        return top == (size - 1);
    }
    bool isEmpty() const {
        return top == -1;
    }
    void Push(T value) {
        if (!isFull()) {
            arr[++top] = value;
        }
    }
    T pop() {
        if (!isEmpty()) {
            return arr[top--];
        } else {
         return T();
        }
    }
    T peekLast() {
        if (!isEmpty()) {
            return arr[top];
        } else {
         return T();
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
