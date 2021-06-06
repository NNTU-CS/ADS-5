// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
struct ITEM {
T data;
ITEM *next;
};

 private:
ITEM *create(T data) {
ITEM *i = new ITEM;
i->data = data;
i->next = nullptr;
return i;
}
ITEM *head;
ITEM *tail;

 public:
TPQueue() : head(nullptr), tail(nullptr) {}
~TPQueue() {
while (head)
pop();
}

void push(const T &data) {
if (tail && head) {
ITEM *temp = head;
if (data.prior > temp->data.prior) {
temp = create(data);
temp->next = head;
head = temp;
} else {
while (temp->next) {
if (temp->next->data.prior < data.prior) {
ITEM *temp2 = create(data);
temp2->next = temp->next;
temp->next = temp2;
break;
} else {
temp = temp->next;
}
}
}
if (!temp->next) {
tail->next = create(data);
tail = tail->next;
}
} else {
head = create(data);
tail = head;
}
}
T pop() {
if (head) {
ITEM *temp = head->next;
T data = head->data;
delete head;
head = temp;
return data;
}
}
};

struct SYM {
char ch;
int prior;
};

#endif // INCLUDE_TPQUEUE_H_
