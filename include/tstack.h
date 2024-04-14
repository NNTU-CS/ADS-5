// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
private:
    T* sA;
    int tI;
 public:
    TStack() : tI(-1) {
        sA = new T[size];
    }
    void pop() {
        if (tI >= 0)
            tI--;
    }
    void push(T item) {
        if (tI < size - 1)
            sA[tI] = item;
    }
    T get() const {
        return sA[tI];
    }
    bool checkEmpty() const {
        return tI == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
