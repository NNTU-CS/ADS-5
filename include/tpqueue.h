// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
private:
    struct ITEM {
        T data;
        ITEM* next;
        ITEM* prev;
    };
    ITEM* head;
    ITEM* tail;
    TPQueue::ITEM* create(const T& data, ITEM* prev) {
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
            ITEM* cur = tail;

            while (cur && data.prior > (cur->data).prior) {
                cur = cur->prev;
            }
            if (cur) {
                ITEM* temp = cur->next;
                cur->next = create(data, cur);
                cur = cur->next;
                cur->next = temp;
                if (temp)
                    temp->prev = cur;
                else
                    tail = cur;
            } else {
                cur = create(data, nullptr);
                cur->next = head;
                head->prev = cur;
                head = cur;
            }
        } else {
            head = create(data, nullptr);
            tail = head;
        }
    }

    T pop() {
        assert(head);
        ITEM* temp = head->next;
        T data = head->data;
        if (temp)
            temp->prev = nullptr;
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
