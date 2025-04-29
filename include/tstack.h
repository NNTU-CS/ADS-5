// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
  private:
  ElementType storage[Capacity];
  int pointer;

 public:
  TStack() : pointer(-1) {}

  bool isVoid() const {
    return pointer == -1;
  }

  bool isFull() const {
    return pointer == Capacity - 1;
  }

  void add(const ElementType& value) {
    if (isFull()) {
      throw std::overflow_error("Stack overflow");
    }
    storage[++pointer] = value;
  }

  ElementType remove() {
    if (isVoid()) {
      throw std::underflow_error("Stack underflow");
    }
    return storage[pointer--];
  }

  ElementType getTop() const {
    if (isVoid()) {
      throw std::underflow_error("Stack empty");
    }
    return storage[pointer];
  }
};

#endif  // INCLUDE_TSTACK_H_
        if (!empty()) {
            --topIndex;
        }    else {
            throw std::underflow_error("Stack underflow");
        }
    }
    T top() const {
        if (!empty()) {
            return data[topIndex];
        }    else {
            throw std::underflow_error("Stack is empty");
        }
    }
    int sizeOfStack() const {
        return topIndex + 1;
    }
};
#endif  // INCLUDE_TSTACK_H_
