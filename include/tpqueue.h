// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
template<typename T>
class TPQueue {
  struct ITEM {
    T data;
    ITEM* next;
    ITEM* last;
  };

 private:
  ITEM* head;
  ITEM* tail;
  TPQueue::ITEM* create(const T& data, ITEM*last) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->last = last;
    return item;
  }

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}

  ~TPQueue() {
    while (head) {
      pop();
    }
  }

  void push(const T& data) {
    if (tail && head) {
      ITEM* cur = tail;
      while (cur && data.prior > (cur->data).prior) {
        cur = cur->last;
      }
      if (cur) {
        ITEM* temp = cur->next;
        cur->next = create(data, cur);
        cur = cur->next;
        cur->next = temp;
        if (temp)
          temp->last = cur;
        else
          tail = cur;
      } else {
        cur = create(data, nullptr);
        cur->next = head;
        head->last = cur;
        head = cur;
      }
    } else {
      head = create(data, nullptr);
      tail = head;
    }
  }

  T pop() {
      ITEM* temp = head->next;
      T data = head->data;
      if (temp)
        temp->last = nullptr;
      delete head;
      head = temp;
      return data;
  }
};

struct SYM {
  char ch;
  int  prior;
};
#endif // INCLUDE_TPQUEUE_H_
