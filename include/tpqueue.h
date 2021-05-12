// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* previous;
    ITEM* next;
  };
  ITEM* strt;
  ITEM* fnsh;
  TPQueue::ITEM* create(const T& data, ITEM* previous) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->previous = previous;
    return item;
  }

 public:
  TPQueue() : strt(nullptr), fnsh(nullptr) {}
  ~TPQueue() {
    while (strt) pop();
  }
  void push(const T& data) {
    if (fnsh && strt) {
      ITEM* crrnt = fnsh;
      while (crrnt && data.prior > (crrnt->data).prior) {
        crrnt = crrnt->previous;
      }
      if (crrnt) {
        ITEM* tmp = crrnt->next;
        crrnt->next = create(data, crrnt);
        crrnt = crrnt->next;
        crrnt->next = tmp;
        if (tmp) {
          tmp->previous = crrnt;
        } else {
          fnsh = crrnt;
        }
      } else {
        crrnt = create(data, nullptr);
        crrnt->next = strt;
        strt->previous = crrnt;
        strt = crrnt;
      }
    } else {
      strt = create(data, nullptr);
      fnsh = strt;
    }
  }
  T pop() {
    assert(strt);
    ITEM* tmp = strt->next;
    T data = strt->data;
    if (tmp) tmp->previous = nullptr;
    delete strt;
    strt = tmp;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
