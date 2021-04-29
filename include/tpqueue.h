// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
  ITEM* head;
  ITEM* tail;

  struct ITEM {
    T data;
    ITEM* next;
    ITEM* prev;
  };

  TPQueue::ITEM* create(const T& data, ITEM*prev) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prev = prev;
    return item;
  }

 public:
  TPQueue() :head(nullptr), tail(nullptr) {}
  ~TPQueue() {
    while (head)
      pop();
  }

  void push(const T& data) {
    if (tail && head) {
      ITEM* current = tail;
      
      while (current && data.prior > (current->data).prior) {
        current = current->prev;
      }
      if (current) {
        ITEM* temp = current->next;
        current->next = create(data, current);
        current = current->next;
        current->next = temp;
        if (temp)
          temp->prev = current;
        else
          tail = current;
      } else {
        current = create(data, nullptr);
        current->next = head;
        head->prev = current;
        head = current;
      }
    } else {
      head = create(data,nullptr);
      tail = head;
    }
  }

  T pop() {
    if (head) {
      ITEM* temp = head->next;
      T data = head->data;
      if (temp)
        temp->prev = nullptr;
      delete head;
      head = temp;
      return data;
    } else {
      return (T)0;
    }
  }

  void print() const {
    ITEM* temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }
};

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
