// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <string>

template<typename T, int Size>
class TStack {
 private:
    T data[Size];
    int t;

 public:
    TStack() : t(0) {}

    T pop() {
        if (t > 0)
            return data[--t];
        else
            throw std::string("empty");
    }

    void push(const T& item) {
        if (t <= Size - 1)
            data[t++] = item;
        else
            throw std::string("full");
    }


    bool isEmpty() {
        return t == 0;
    }

    T get() {
        if (!isEmpty())
            return data[t - 1];
        else
            throw std::string("empty");
    }
};

#endif  // INCLUDE_TSTACK_H_
