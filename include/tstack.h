// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
   T data[100];
   int top;
 public:
   TStack() : top(-1) {}
   void push(T item) {
     if (!isFull)
       data[++top] = item;
     else
       throw std::string("Full");
   }
   bool isFull() {
     return top == -1;
   }
   bool isEmpty() {
     return top == 0;
   }
   T pop() {
     if (!isEmpty)
       return data[--top];
     else
       throw std::string("Empty");
   }
   T show() {
     return data[top];
   }
};

#endif  // INCLUDE_TSTACK_H_
