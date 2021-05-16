// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
#include <utility>

template<typename T>
class TPQueue {
  // Сюда помещается описание структуры "Очередь с приоритетами"
 public:
void push(const T &data) {
LListQueue<T> new_queue;
while (queue_.size() > 0 && queue_.get().prior >= data.prior) {
new_queue.push(queue_.pop());
}
new_queue.push(data);
new_queue.append(std::move(queue_));
queue_ = std::move(new_queue);
}
T pop() { return queue_.pop(); }
void print() { queue_.print(); }
 private:
LListQueue<T> queue_;
};

template<typename T>
class LListQueue {
struct ITEM {
T data;
ITEM *prev;
ITEM *next;

~ITEM() { delete next; }
};

 public:
LListQueue() : size_(0), head_(nullptr), tail_(nullptr) {}

~LListQueue() { delete head_; }

void push(const T &data) {
++size_;

if (tail_ == nullptr) {
head_ = tail_ = new ITEM{data, nullptr, nullptr};
} else {
tail_->next = new ITEM{data, tail_, nullptr};
tail_ = tail_->next;
}
}

T pop() {
assert(size_ > 0);

ITEM *top = head_;

head_ = head_->next;
if (head_) { head_->prev = nullptr; }

T data = top->data;
top->prev = nullptr;
top->next = nullptr;

delete top;

--size_;

return data;
}

T get() const {
assert(size_ > 0);

return head_->data;
}

void print() const {
ITEM *curr = head_;
while (curr) {
std::cout << curr->data << ' ';
curr = curr->next;
}
std::cout << '\n';
}

size_t size() const { return size_; }

LListQueue & operator = (LListQueue &&q) {
delete head_;

size_ = q.size_;
head_ = q.head_;
tail_ = q.tail_;

q.size_ = 0;
q.head_ = nullptr;
q.tail_ = nullptr;

return *this;
}

void append(LListQueue &&q) {
size_ += q.size_;

if (tail_ == nullptr) {
head_ = q.head_;
tail_ = q.tail_;
} else {
tail_->next = q.head_;
if (tail_->next) { tail_->next->prev = tail_; }
}

q.size_ = 0;
q.head_ = nullptr;
q.tail_ = nullptr;
}

 private:
size_t size_;
ITEM *head_;
ITEM *tail_;
};

struct SYM {
  char ch;
  int  prior;
};

std::ostream & operator<<(std::ostream &os, const SYM &s) {
return os << '{' << s.ch << ", " << s.prior << '}';
}

#endif // INCLUDE_TPQUEUE_H_
