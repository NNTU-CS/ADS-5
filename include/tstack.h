// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <stdexcept>

template<typename ElementType, int kCapacity>
class CustomStack {
 private:
    ElementType stackStorage[kCapacity];
    int currentPosition;

 public:
    CustomStack() : currentPosition(-1) {}
    bool isStackEmpty() const {
        return currentPosition < 0;
    }
    bool isStackFull() const {
        return currentPosition >= kCapacity - 1;
    }
    void addElement(const ElementType& newItem) {
        if (isStackFull()) {
            throw std::runtime_error("Stack capacity exceeded");
        }
        stackStorage[++currentPosition] = newItem;
    }
    void removeElement() {
        if (isStackEmpty()) {
            throw std::runtime_error("Cannot remove from empty stack");
        }
        --currentPosition;
    }
    ElementType& peekTop() {
        if (isStackEmpty()) {
            throw std::runtime_error("Cannot access empty stack");
        }
        return stackStorage[currentPosition];
    }
    const ElementType& peekTop() const {
        if (isStackEmpty()) {
            throw std::runtime_error("Cannot access empty stack");
        }
        return stackStorage[currentPosition];
    }
};
#endif  // INCLUDE_TSTACK_H_
