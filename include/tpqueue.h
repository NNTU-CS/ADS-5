template<typename T>
class TPQueue {
  // Сюда помещается описание структуры "Очередь с приоритетами"
struct Item {
T data;
Item* next;
Item* prev;
};
private:
TPQueue::Item* create(const T&);
Item* head;
Item* tail;
public:
TPQueue() : head(nullptr), tail(nullptr) {}
~TPQueue();
void push(const T&);
T pop();
};
template <typename T>
typename TPQueue <T>::Item* TPQueue <T>::create(const T& data) {
Item* item = new Item;
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
Item* l = tail;
while (l && data.prior > l->data.prior) {
l = l->prev;
}
if (l) {
Item* p;
Item* p2;
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
Item* temp = head->next;
T data = head->data;
if (temp)
temp->prev = nullptr;
delete head;
head = temp;
return data;
}

struct SYM
{ 
  char ch;
	int prior;
}

