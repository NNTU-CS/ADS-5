// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class tstack {
  // добавьте код стека
 private:
    T* array;
    int beg;

 public:
    tstack() : beg(-1) {
        array = new T[size];
    }
    T get() const {
        return array[beg];
    }
    bool empty() const {
        return beg == -1;
    }
    bool isfull() const {
        return beg == size - 1;
    }
    void pop() {
        if (beg >= 0)
            beg--;
    }
    void push(T a) {
        if (beg < size - 1)
            array[++beg] = a;
    }
};

#endif  // INCLUDE_TSTACK_H_
