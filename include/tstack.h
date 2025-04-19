// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template <typename T, int size>
class TStack {
 private:
  T elements[size];
  int head_pos;

 public:
  TStack() : head_pos(-1) {}

  void push(const T& item) {
    if (head_pos >= size - 1) throw std::overflow_error("Stack full");
    elements[++head_pos] = item;
  }

  T remove() {
    if (head_pos < 0) throw std::underflow_error("Stack empty");
    return elements[head_pos--];
  }

  T check() const {
    if (head_pos < 0) throw std::underflow_error("No elements");
    return elements[head_pos];
  }

  bool hasElements() const {
    return head_pos != -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
