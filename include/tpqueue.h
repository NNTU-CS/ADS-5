// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* prev;
    ITEM* next;
  };
  ITEM* first;
  ITEM* last;
  TPQueue::ITEM* create(const T& data, ITEM* prev) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prev = prev;
    return item;
  }

 public:
  TPQueue() : first(nullptr), last(nullptr) {}
  ~TPQueue() {
    while (first) pop();
  }
  void push(const T& data) {
    if (last && first) {
      ITEM* cur = last;
      while (cur && data.prior > (cur->data).prior) {
        cur = cur->prev;
      }
      if (cur) {
        ITEM* tmp = cur->next;
        cur->next = create(data, cur);
        cur = cur->next;
        cur->next = tmp;
        if (tmp) {
          tmp->prev = cur;
        } else {
          last = cur;
        }
      } else {
        cur = create(data, nullptr);
        cur->next = first;
        first->prev = cur;
        first = cur;
      }
    } else {
      first = create(data, nullptr);
      last = first;
    }
  }
  T pop() {
    assert(first);
    ITEM* tmp = first->next;
    T data = first->data;
    if (tmp) tmp->prev = nullptr;
    delete first;
    first = tmp;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
