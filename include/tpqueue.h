// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
  struct part {
    T t;
    part* next;
  };
  part* head;

 public:
  TPQueue() :head(nullptr) {}
  ~TPQueue() {
    while (head) {
      part* lnext = head->next;
      delete head;
      head = lnext;
    }
  }

  T pop() {
    T x = head->t;
    part* lnext = head->next;
    delete head;
    head = lnext;
    return x;
  }

  part* create(const T& x) {
    part *y = new part;
    y->t = x;
    y->next = nullptr;
    return y;
  }

  void push(const T& x) {
    if (head == nullptr) {
      head = create(x);
    } else {
      part* y = create(x);
      part* lnext = head;
      part* lbefore = nullptr;
      bool er = true;
      while (lnext != nullptr) {
        if (lnext->t.prior < y->t.prior) {
          er = false;
          y->next = lnext;
          if (lbefore != nullptr)
            lbefore->next = y;
          else
            head = y;
          break;
        }
        lbefore = lnext;
        lnext = lnext->next;
      }
      if (er)
        lbefore->next = y;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif // INCLUDE_TPQUEUE_H_
