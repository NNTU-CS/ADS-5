// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename T, int kSize>
class TStack {
 private :
     T data[kSize];
     int top = 0;

 public :
     void push(const T &item) {
         if (top >= kSize)
             throw std::overflow_error("Full!");
         data[top++] = item;
     }

     T pop() {
         if (top <= 0) {
             throw std::underflow_error("Empty!");
         }
         return data[--top];
     }

     bool isEmpty() const {
         return top == 0;
     }

     const T& get() const {
         if (isEmpty())
             throw std::underflow_error("Empty!");
         return data[top - 1];
     }
};

#endif  // INCLUDE_TSTACK_H_

