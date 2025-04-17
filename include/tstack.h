// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename DataType, int MaxSize>
class TStack {
 private:
    DataType elementsStorage[100];
    int stackPointer;

 public:
    TStack() : stackPointer(-1) {}

    void push(DataType valueToAdd) {
      if (isFull()) {
        throw std::string("Stack is full!");
      } else {
        elementsStorage[++stackPointer] = valueToAdd;
      }
    }

    const DataType& pop() {
      if (isEmpty()) {
        throw std::string("Stack is empty!");
      } else {
        return elementsStorage[stackPointer--];
      }
    }

    bool isEmpty() const {
      return stackPointer == -1;
    }

    bool isFull() const {
      return stackPointer == MaxSize - 1;
    }

    const DataType& get() const {
      return elementsStorage[stackPointer];
    }
};
#endif  // INCLUDE_TSTACK_H_
