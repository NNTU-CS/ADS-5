// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
  T core;
  TPQueue* next;
  TPQueue* prev;
  TPQueue* begin;

 public:
  TPQueue() {
    next = nullptr;
    prev = nullptr;
    begin = nullptr;
  }
void push(const T &element) {
    if (begin != nullptr) {
      TPQueue* step = new TPQueue;
      step->core = element;
      step->prev = prev;
      prev = step;
      next->next = step;
      next = step;
      if (step->core.prior > step->prev->core.prior) {
        TPQueue* step_prev = step->prev;
        TPQueue* step_this = step;
        while (step_prev && step_this->core.prior > step_prev->core.prior) {
          T x = step_this->core;
          step_this->core = step_prev->core;
          step_prev->core = x;
          step_this = step_this->prev;
          step_prev = step_prev->prev;
        }
      }
    } else {
      TPQueue* step = new TPQueue;
      step->core = element;
      begin = step;
      prev = step;
      next = step;
    }
  }
T pop() {
if (begin != nullptr) {
T x = begin->core;
begin = begin->next;
return x;
}
}
};
struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
