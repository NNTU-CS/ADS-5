// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
 private:
struct ITEM {
T data;
ITEM* follow;
ITEM* previous;
};
ITEM* head;
ITEM* tail;
TPQueue::ITEM* create(const T& data, ITEM*previous) {
ITEM* item = new ITEM;
item->data = data;
item->follow = nullptr;
item->previous = previous;
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
current = current->previous;
}
if (current) {
ITEM* temp = current->follow;
current->follow = create(data, current);
current = current->follow;
current->follow = temp;
if (temp)
temp->previous = current;
else
tail = current;
} else {
current = create(data, nullptr);
current->follow = head;
head->previous = current;
head = current;
}
} else {
head = create(data, nullptr);
tail = head;
}
}
T pop() {
assert(head);
ITEM* temp = head->follow;
T data = head->data;
if (temp)
temp->previous = nullptr;
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
