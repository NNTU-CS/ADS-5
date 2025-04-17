// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static constexpr int kMaxSize = size;
  T data[kMaxSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void push(const T& value) {
    if (topIndex < kMaxSize - 1) {
      data[++topIndex] = value;
    }
  }

  T pop() {
    return topIndex >= 0 ? data[topIndex--] : T();
  }

  T top() const {
    return topIndex >= 0 ? data[topIndex] : T();
  }

  bool isEmpty() const {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
