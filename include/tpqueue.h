// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template < typename T >
  class TPQueue {
     private:
       struct ITEM {
        T data;
        ITEM * next;
      };
    ITEM * head;
    ITEM * create(const T & data) {
      ITEM * item = new ITEM;
      item -> data = data;
      item -> next = nullptr;
      return item;
    }

   public:
      TPQueue(): head(nullptr) {}~TPQueue() {
        while (head)
          pop();
      }
    void push(const T & data) {
      if (head == nullptr) {
        head = create(data);
      } else {
        ITEM * item1 = head;
        ITEM * item2 = head;
        while (data.prior <= item1 -> data.prior && item1 -> next != nullptr) {
          item1 = item1 -> next;
        }
        if (item1 == head && data.prior > item1 -> data.prior) {
          item1 = create(data);
          item1 -> next = head;
          head = item1;
        } else if (item1 == head && data.prior <= item1 -> data.prior) {
          item1 = head -> next;
          head -> next = create(data);
          head -> next -> next = item1;
        } else if (item1 -> next == nullptr &&
          item1 -> data.prior >= data.prior) {
          item1 -> next = create(data);
        } else {
          while (item2 -> next != item1) {
            item2 = item2 -> next;
          }
          item2 -> next = create(data);
          item2 -> next -> next = item1;
        }
      }
    }
    T pop() {
      assert(head);
      ITEM * tmp = head -> next;
      T data = head -> data;
      delete head;
      head = tmp;
      return data;
    }
  };

struct SYM {
  char ch;
  int prior;
};

#endif // INCLUDE_TPQUEUE_H_
