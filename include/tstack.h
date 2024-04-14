// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  int currentFreePosition = 0;
  T* data = new T[size];

 public:
  void push(T element) {
  if (currentFreePosition == size) {
      return;
  }
  data[currentFreePosition] = element;
  currentFreePosition++;
  }
  T pop() {
  if (currentFreePosition == 0) {
      throw std::exception();
  }
  currentFreePosition--;
  return data[currentFreePosition];
  }
  T seeTop() {
  if (currentFreePosition == 0) {
      throw std::exception();
  }
  return data[currentFreePosition - 1];
  }
  T seeBottom() {
  if (currentFreePosition == 0) {
      throw std::exception();
  }
  return data[0];
  }
  bool isEmpty() {
  if (currentFreePosition == 0) {
      return true;
  }
  return false;
  }
};

#endif  // INCLUDE_TSTACK_H_
