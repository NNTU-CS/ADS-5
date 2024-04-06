// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T* stackArray;
    int topIndex;
 public:
    TStack() : topIndex(-1) {
        stackArray = new T[size];
    }
    void pop() {
        if (topIndex >= 0)
            topIndex--;
    }
    void push(T item) {
        if (topIndex < size - 1)
            stackArray[++topIndex] = item;
    }
    T get() const {
        return stackArray[topIndex];
    }
    bool checkEmpty() const {
        return topIndex == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
