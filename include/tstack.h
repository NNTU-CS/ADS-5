// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
   T data[100];
   int perem;
 public:
   TStack() : perem(-1) {}
   void push(T item) {
     if (!isFull)
       data[++perem] = item;
     else
       throw std::string("Full");
   }
   bool isFull() const {
     return perem == -1;
   }
   bool empty() const {
     return perem == 0;
   }
   T pop() {
     if (!empty)
       return data[--perem];
     else
       throw std::string("Empty");
   }
   T top() const {
     return data[perem];
};

#endif  // INCLUDE_TSTACK_H_
