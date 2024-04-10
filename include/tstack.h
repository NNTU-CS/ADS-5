// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
template<typename T, int size>
class TStack {
 private:
    T arr[100];
    int k;

 public:
    TStack(): k(-1) {}
    void push(T value) {
      if (!isFull())
        arr[++k] = value;
      else
        throw std::string("full!");
    }
    T get() const {
      return arr[k];
    }
    T pop() {
      if (isEmpty())
        throw std::string("empty!");
      else
        return arr[k--];
    }
    bool isFull() const {
      return k == size - 1;
    }
    bool isEmpty() const {
      return k == -1;
    }
};

};

#endif  // INCLUDE_TSTACK_H_
