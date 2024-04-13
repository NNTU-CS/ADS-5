// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
    T mas[100];
    int per;

 public:
    TStack(): per(-1) {}
    void push(T per2) {
      if (!Full())
        mas[++per] = per2;
      else
        throw std::string("Full");
    }
    T get() const {
      return mas[per];
    }
    T pop() {
      if (Empty())
        throw std::string("Empty");
      else
        return mas[per--];
    }
    bool Empty() const {
      return per == -1;
    }
    bool Full() const {
      return per == size - 1;
    }
};

#endif  // INCLUDE_TSTACK_H_
