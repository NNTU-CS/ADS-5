// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
  struct ITEM {
    T res;
    ITEM *next;
  };
  
 private:
  ITEM *head;
  ITEM *tail;
  ITEM *create(T res) {
    ITEM *i = new ITEM;
    i->res = res;
    i->next = nullptr;
    return i;
  }
  
 public:
  TPQueue() :head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head)
      pop();
  }
  void push(const T &res) {
    if (tail && head) {
      ITEM *temp = head;
      if (temp->res.prior < res.prior) {
        temp = create(res);
        temp->next = head;
        head = temp;
      } else {
        while (temp->next) {
          if (temp->next->res.prior < res.prior) {
            ITEM *i = create(res);
            i->next = temp->next;
            temp->next = i;
            break;
          } else {
            temp = temp->next;
          }
        }
      }
      if (!temp->next) {
        tail->next = create(res);
        tail = tail->next;
      }
    } else {
      head = create(res);
      tail = head;
    }
  }
  T pop() {
    ITEM *temp = head->next;
    T res = head->res;
    delete head;
    head = temp;
    return res;
  }
};
struct SYM {
  char ch;
  int  prior;
};
#endif // INCLUDE_TPQUEUE_H_
