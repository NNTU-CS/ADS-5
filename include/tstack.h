// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
     T* ptr;
     int z;

 public:
    TStack() : z(0) {
      ptr = new T[size];
    }
    void PushUp(const T& c) {
      if (size - 1 >= z) {
        ptr[z++] = c;
      } else {
       throw std::string("fall!");
      }
    }
    T PopBack() {
     if (z > 0) {
      return ptr[--z];
     } else {
      throw std::string("empty");
     }
    }
    bool IfZero() const {
     return z == 0;
    }
    T ElemUp() const {
     if (z > 0) {
      return ptr[z - 1];
     } else {
      throw std::string("fall!");
     }
    }
};
#endif  // INCLUDE_TSTACK_H_
