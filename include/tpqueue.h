// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
  struct ITEM {
    T massiv;
    ITEM *next;
  };

 private:
  ITEM *start;
  ITEM *stop;
  ITEM *create(T massiv) {
    ITEM *t = new ITEM;
    t->massiv = massiv;
    t->next = nullptr;
    return t;
  }

 public:
  TPQueue() :start(nullptr), stop(nullptr) {}
  ~TPQueue() {
    while (start) {
      pop();
    }
  }

  void push(const T &massiv) {
    if (stop && start) {
      ITEM *temp = start;

      if (temp->massiv.prior < massiv.prior) {
        temp = create(massiv);
        temp->next = start;
        start = temp;
      } else {
        while (temp->next) {
          if (temp->next->massiv.prior < massiv.prior) {
            ITEM *t = create(massiv);
            t->next = temp->next;
            temp->next = t;
            break;
          } else {
            temp = temp->next;
          }
        }
      }

      if (!temp->next) {
        stop->next = create(massiv);
        stop = stop->next;
      }
    } else {
      start = create(massiv);
      stop = start;
    }
  }

  T pop() {
    ITEM *temp = start->next;
    T massiv = start->massiv;
    delete start;
    start = temp;
    return massiv;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif // INCLUDE_TPQUEUE_H_
