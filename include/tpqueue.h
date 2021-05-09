// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <typename T>
class TPQueue {
struct ITEM {
T data;
ITEM* next;
};
 public:
TPQueue() : head(nullptr), tail(nullptr) {}
~TPQueue();
void push(const T&);
T pop();
 private:
ITEM* create(const T& data) {
ITEM* item = new ITEM;
item->data = data;
item->next = nullptr;
return item;
}
ITEM* head;
ITEM* tail;
};
template < typename T >
TPQueue <T>::~TPQueue() {
while (head)
pop();
}
template < typename T >
void TPQueue <T>::push(const T& data) {
if (head == nullptr) {
head = create(data);
tail = head;
} else {
ITEM* temp = head;
while (temp->data.prior >= data.prior) {
temp = temp->next;
if (temp == nullptr)
break;
}
if (temp == nullptr) {
temp = create(data);
tail->next = temp;
tail = temp;
} else {
if (temp == head) {
head = create(data);
head->next = temp;
} else {
ITEM* temp1 = temp;
temp = create(data);
temp->next = temp1;
}
}
}
}
template <typename T>
T TPQueue <T>::pop() {
ITEM* temp = head -> next;
T data = head -> data;
delete head;
head = temp;
return data;
}
struct SYM {
char ch;
int prior;
};

#endif // INCLUDE_TPQUEUE_H_
