// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
struct ITEM {
T data;
ITEM* next;
ITEM* prev;
};
 private:
    TPQueue::ITEM* create(const T&);
    ITEM* head;
    ITEM* tail;
 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
};

template <typename T>
typename TPQueue <T>::ITEM* TPQueue <T>::create(const T& data) {
  ITEM* item = new ITEM;
  item->data.ch = data.ch;
  item->data.prior = data.prior;
  item->next = nullptr;
  item->prev = nullptr;
  return item;
}
template <typename T>
TPQueue <T >::~TPQueue() {
  while (head)
    pop();
}
template <typename T>
void TPQueue <T>::push(const T& data) {
  if (tail && head) {
    ITEM* l = tail;
    while (l && data.prior > l->data.prior) {
      l = l->prev;
    }
    if (l) {
      ITEM* p;
      ITEM* p2;
      p = l->next;
      l->next = create(data);
      p2 = l->next;
      p2->prev = l;
      l = p2;
      l->next = p;
      if (p) {
        p->prev = l;
      } else {
        tail = l;
      }
    } else {
      l = create(data);
      l->next = head;
      head->prev = l;
      head = l;
    }
  } else {
    head = create(data);
    tail = head;
  }
}
template <typename T>
T TPQueue <T>::pop() {
  assert(head);
  ITEM* temp = head->next;
  T data = head->data;
  if (temp)
    temp->prev = nullptr;
  delete head;
  head = temp;
  return data;
}

struct SYM {
  char ch;
  int  prior;
};
#endif // INCLUDE_TPQUEUE_H_
