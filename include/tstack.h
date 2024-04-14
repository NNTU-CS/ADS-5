// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T *stackArray;
    int topIndex;

 public:
    TStack() {
        stackArray = new T[size];
        topIndex = -1;
    }

    ~TStack() {
        delete[] stackArray;
    }

    void push(T item) {
        if (topIndex != size - 1) {
            topIndex++;
            stackArray[topIndex] = item;
        }
    }

    T pop() {
        if (topIndex != -1) {
            T element = stackArray[topIndex];
            topIndex--;
            return element;
        } else {
            return T();
        }
    }

    T get() const {
        if (topIndex == -1) {
            return T();
        } else {
            return stackArray[topIndex];
        }
    }

    bool isempty() const {
        return topIndex == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
