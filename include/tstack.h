// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  // добавьте код стека
 private:
    T* arr;
    int begin;

 public:
    TStack() : begin(-1) {
        arr = new T[size];
    }
    T get() const {
        return arr[begin];
    }
    bool isemp() const {
        return begin == -1;
    }
    bool full() const {
        return begin == size - 1;
    }
    void pop() {
        if (begin >= 0)
            begin--;
    }
    void push(T a) {
        if (begin < size - 1)
            arr[++begin] = a;
    }
};
#endif  // INCLUDE_TSTACK_H_
