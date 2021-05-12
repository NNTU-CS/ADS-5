// Copyright 2021 NNTU-CS
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T data;
    ITEM* prior;
    ITEM* prev;
    ITEM* next;
  };
  ITEM* start;
  ITEM* end;
  TPQueue::ITEM* create(const T& data, ITEM* prior) {
  TPQueue::ITEM* create(const T& data, ITEM* prev) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prior = prior;
    item->prev = prev;
    return item;
  }

@@ -28,25 +28,25 @@ class TPQueue {
  }
  void push(const T& data) {
    if (end && start) {
      ITEM* this = end;
      while (this && data.prior > (this->data).prior) {
        this = this->prior;
      ITEM* curr = end;
      while (curr && data.prior > (curr->data).prior) {
        curr = curr->prev;
      }
      if (this) {
        ITEM* tmp = this->next;
        this->next = create(data, this);
        this = this->next;
        this->next = tmp;
      if (curr) {
        ITEM* tmp = curr->next;
        curr->next = create(data, curr);
        curr = curr->next;
        curr->next = tmp;
        if (tmp) {
          tmp->prior = this;
          tmp->prev = curr;
        } else {
          end = this;
          end = curr;
        }
      } else {
        this = create(data, nullptr);
        this->next = start;
        start->prior = this;
        start = this;
        curr = create(data, nullptr);
        curr->next = start;
        start->prev = curr;
        start = curr;
      }
    } else {
      start = create(data, nullptr);
      end = start;
    }
  }
  T pop() {
    assert(start);
    ITEM* tmp = start->next;
    T data = start->data;
    if (tmp) tmp->prior = nullptr;
    if (tmp) tmp->prev = nullptr;
    delete start;
    start = tmp;
    return data;
  }
};
struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
