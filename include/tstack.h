// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int kMaxStackSize = 100;
  T items[kMaxStackSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& item) {
    if (topIndex < kMaxStackSize - 1) {
      items[++topIndex] = item;
    }
  }

  void pop() {
    if (topIndex >= 0) {
      --topIndex;
    }
  }

  T top() const {
    if (topIndex >= 0) {
      return items[topIndex];
    }
    return T();
  }

  bool isEmpty() const {
    return topIndex < 0;
  }
};

#endif  // INCLUDE_TSTACK_H_
