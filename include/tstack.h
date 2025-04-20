// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    T data[size];
    int topIndex;
    bool errorFlag;

 public:
    TStack() : topIndex(-1), errorFlag(false) {}

    bool push(const T& value) {
        if (topIndex >= size - 1) {
            errorFlag = true;
            return false;
        }
        data[++topIndex] = value;
        errorFlag = false;
        return true;
    }

    bool pop(T& out) {
        if (isEmpty()) {
            errorFlag = true;
            return false;
        }
        out = data[topIndex--];
        errorFlag = false;
        return true;
    }

    bool top(T& out) const {
        if (isEmpty()) {
            return false;
        }
        out = data[topIndex];
        return true;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == size - 1;
    }

    int count() const {
        return topIndex + 1;
    }

    bool hasError() const {
        return errorFlag;
    }
};

#endif  // INCLUDE_TSTACK_H_
