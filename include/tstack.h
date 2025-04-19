// Copyright 2021 NNTU-CS
#ifndef GUARD_TSTACK_H
#define GUARD_TSTACK_H

template <typename T, int max_depth>
class TStack {
private:
  T elements[max_depth];
  int head_pos;
public:
  TStack() : head_pos(-1) {}

  void push(const T& item) {
    if (head_pos >= max_depth - 1) throw std::overflow_error("Stack full");
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

#endif  // GUARD_TSTACK_H
