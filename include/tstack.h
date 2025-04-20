// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int Size>
class TStack {
 private:
  T data[Size];
  int top_index;

 public:
  TStack() : top_index(-1) {}

  void push(const T& value) {
    if (top_index >= Size - 1) throw std::overflow_error("Stack full");
    data[++top_index] = value;
  }

  T remove() {
    if (top_index < 0) throw std::underflow_error("Stack empty");
    return data[top_index--];
  }

  T check() const {
    if (top_index < 0) throw std::underflow_error("No elements");
    return data[top_index];
  }

  bool hasElements() const {
    return top_index >= 0;
  }
};

#endif  // INCLUDE_TSTACK_H_
