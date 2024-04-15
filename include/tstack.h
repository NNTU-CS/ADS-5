// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* arr;
    int top;

 public:
    TStack() {
        arr = new T[size];
        top = -1;
    }
    ~TStack() {
        delete[] arr;
    }
    bool isEmpty() const {
        return top == -1;
    }
    T pop() {
        if (top != -1) {
            T element = arr[top];
            top--;
            return element;
        } else {
            return T();
        }
    }
    T get() const {
        if (top == -1) {
            return T();
        } else {
            return arr[top];
        }
    }
    void push(T item) {
        if (top != size - 1) {
            arr[++top] = item;
        }
    }
};

#endif  // INCLUDE_TSTACK_H_
