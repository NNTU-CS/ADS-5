// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  T el[size];
  int index;

 public:
  TStack() : index(-1) {}

  void push(const T& value) {
    if (index >= size - 1) throw std::overflow_error("Stack full");
    el[++index] = value;
  }

  T remove() {
    if (index < 0) throw std::underflow_error("Stack empty");
    return el[index--];
  }

  T check() const {
    if (index < 0) throw std::underflow_error("No elements");
    return el[index];
  }

  bool hasElements() const {
    return index >= 0;
  }
};

#endif  // INCLUDE_TSTACK_H_
