// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int max_size>
class TStack {
 private:
    const int Ksize = max_size;
    T array[100];
    int top_index;

 public:
    TStack() : top_index(0) {}
    T get() {
        if (!isEmpty()) {
            return array[top_index - 1];
        } else {
            throw std::string("Empty");
        }
    }
    bool isEmpty() {
        return top_index == 0;
    }
    bool isFull() {
        return top_index == max_size - 1;
    }
    T pop() {
        if (top_index > 0) {
            return array[--top_index];
        } else {
            throw std::string("Empty");
        }
    }
    void push(const T& item) {
        if (top_index <= max_size - 1) {
            array[top_index++] = item;
        } else {
            throw std::string("Full");
        }
    }
};
#endif  // INCLUDE_TSTACK_H_
