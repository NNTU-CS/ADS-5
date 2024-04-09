// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    T stackarr[100];
    int headIndex;

 public:
    TStack(): headIndex(-1) {}
    void push(T value) {
      if (!isFull())
        stackarr[++headIndex] = value;
      else
        throw std::string("Full");
    }
    T get() const {
      return stackarr[headIndex];
    }
    T pop() {
      if (isEmpty())
        throw std::string("Empty");
      else
        return stackarr[headIndex--];
    }
    bool isEmpty() const {
      return headIndex == -1;
    }
    bool isFull() const {
      return headIndex == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
