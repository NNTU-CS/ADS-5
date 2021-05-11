// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue
{
    struct ITEM
    {
        T data;
        ITEM* next;
        ITEM* prev;
    };
public:
    TPQueue() :head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
private:
    TPQueue::ITEM* create(const T&);
    ITEM* head;
    ITEM* tail;
};


template<typename T>
typename TPQueue<T>::ITEM* TPQueue<T>::create(const T& data) {
    ITEM* item = new ITEM;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}
template<typename T>
TPQueue<T>::~TPQueue() {
    while (head)
        pop();
}
template<typename T>
void TPQueue<T>::push(const T& dat) {
    if (head == nullptr) {
        head = create(dat);
        tail = head;
    } else if (tail->data.prior >= dat.prior) {
        if (tail->data.ch == dat.ch)
            tail->data = dat;
        else
        {
            tail->next = create(dat);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = create(dat);
        head = tail->prev;
        head->next = tail;
    } else {
        ITEM* tmp = tail;
        while (tmp != head && tmp->data.prior < dat.prior) {
            tmp = tmp->prev;
        }
        if (tmp->data.prior == dat.prior) {
            ITEM* cell = new ITEM;
            cell->next = tmp->next;
            cell->prev = tmp;
            cell->data = dat;
            tmp->next->prev = cell;
            tmp->next = cell;
        }
        if (tmp == head && tmp->data.prior < dat.prior) {
            head->prev = create(dat);
            head = head->prev;
            head->next = tmp;
        }
    }
}
template<typename T>
T TPQueue<T>::pop()
{
    if (head) {
        ITEM* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template<typename T>
void TPQueue<T>::print() const
{
    ITEM* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
