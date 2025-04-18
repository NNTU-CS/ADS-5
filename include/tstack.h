// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

const int kMaxStackSize = 1000;

template<typename T, int size>
class TStack {
 private:
    static_assert(size <= kMaxStackSize, "Stack size exceeds allowed maximum.");
    T elementStorage[kMaxStackSize];
    int stackPointer;

 public:
    TStack() : stackPointer(-1) {}

    void insertElement(const T& newItem) {
        if (isComplete()) {
            throw std::runtime_error("Stack overflow");
        }
        elementStorage[++stackPointer] = newItem;
    }

    T removeLast() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow");
        }
        return elementStorage[stackPointer--];
    }

    bool isComplete() const {
        return stackPointer >= size - 1;
    }

    bool isEmpty() const {
        return stackPointer < 0;
    }

    const T& peekTop() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return elementStorage[stackPointer];
    }
};
#endif  // INCLUDE_TSTACK_H_
