// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 public:
    TStack() : pointer(-1) {}
    bool isVoid() const { return pointer == -1; }
    bool isFull() const { return pointer == size - 1; }
    void add(const T& value) {
        if (isFull()) throw std::overflow_error("Stack overflow");
        storage[++pointer] = value;
    }
    T remove() {
        if (isVoid()) throw std::underflow_error("Stack underflow");
        return storage[pointer--];
    }
    T getTop() const {
        if (isVoid()) throw std::underflow_error("Stack empty");
        return storage[pointer];
    }
 private:
    T storage[size];
    int pointer;
};
#endif // INCLUDE_TSTACK_H_
