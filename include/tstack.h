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
    };
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
        else {
            throw std::string("Full");
        }
    }
    T pop() {
        if (!isEmpty()) {
            return arr[top--];
        }
        else {
            throw std::string("Empty");
        }
    }
    T peekLast() {
        if (!isEmpty()) {
            return arr[top];
        }
    }
    void Print() {
        std::cout << pop() << " ";
    }
};

#endif  // INCLUDE_TSTACK_H_
