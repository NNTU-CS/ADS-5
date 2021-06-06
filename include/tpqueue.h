// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
struct ITEM {
T data;
ITEM * next;
};

 private:
  ITEM * create(const T &data) {
  ITEM * item = new ITEM;
  item->data = data;
  item->next = nullptr;
  return item;
  }

ITEM * head;
ITEM * tail;

 public:
  TPQueue(): head(nullptr), tail(nullptr) {}

~TPQueue() {
while (head)
pop();
}

void push(const T& data) {
if (!(tail && head)) {
head = create(data);
tail = head;
} else if (tail == head) {
if (data.prior > head->data.prior) {
auto *temp = head;
head = create(data);
head->next = temp;
} else {
head->next = create(data);
tail = head->next;
}
} else {
if (data.prior > head->data.prior) {
auto *temp = head;
head = create(data);
head->next = temp;
} else {
auto *temp = head;
while (temp != tail) {
if (data.prior > temp->next->data.prior) {
ITEM *item = create(data);
item->next = temp->next;
temp->next = item;
break;
} else {temp = temp->next;}
}
if (temp = tail) {
tail = create(data);
temp->next = tail;
}
}
}
}
T pop() {
if (head) {
T data = head->data;
if (head == tail) {
delete head;
head = tail = nullptr;
return data;
} else {
ITEM *temp = head->next;
delete head;
head = temp;
return data;
}
}
}
};

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
