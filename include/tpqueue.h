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
  ITEM* head;
  ITEM* tail;
  TPQueue::ITEM* create(const T& data, ITEM* previous) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->previous = previous;
    return item;
  }

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head) pop();
  }
  void push(const T& data) {
    if (tail && head) {
      ITEM* mom = tail;
      while (mom && data.prior > (mom->data).prior) {
        mom = mom->previous;
      }
      if (mom) {
        ITEM* tmp = mom->next;
        mom->next = create(data, mom);
        mom = mom->next;
        mom->next = tmp;
        if (tmp) {
          tmp->previous = mom;
        } else {
          tail = mom;
        }
      } else {
        mom = create(data, nullptr);
        mom->next = head;
        head->previous = mom;
        head = mom;
      }
    } else {
      head = create(data, nullptr);
      tail = head;
    }
  }
  T pop() {
    assert(head);
    ITEM* tmp = head->next;
    T data = head->data;
    if (tmp) tmp->previous = nullptr;
    delete head;
    head = tmp;
    return data;
  }
};

struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
