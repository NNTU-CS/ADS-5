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
    };
    ITEM* head;
    ITEM* create(const T &data) {
        ITEM* item = new ITEM;
        item->data = data;
        item->next = nullptr;
        return item;
    }

 public:
    TPQueue() :head(nullptr) {}
    ~TPQueue() {
        while (head)
            pop();
    }
    void push(const T& data) {
        if (head == nullptr) {
            head = create(data);
        } else {
            ITEM* tmp1 = head;
            ITEM* tmp2 = head;
            while (data.prior <= tmp1->data.prior && tmp1->next != nullptr) {
                tmp1 = tmp1->next;
            }
            if (tmp1 == head && data.prior > tmp1->data.prior) {
                tmp1 = create(data);
                tmp1->next = head;
                head = tmp1;
            } else if (tmp1 == head && data.prior <= tmp1->data.prior) {
                tmp1 = head->next;
                head->next = create(data);
                head->next->next = tmp1;
            } else if (tmp1->next == nullptr
                       && tmp1->data.prior >= data.prior) {
                tmp1->next = create(data);
            } else {
                while (tmp2->next != tmp1) {
                    tmp2 = tmp2->next;
                }
                tmp2->next = create(data);
                tmp2->next->next = tmp1;
            }
        }
    }
    T pop() {
        assert(head);
        ITEM* tmp = head->next;
        T data = head->data;
        delete head;
        head = tmp;
        return data;
    }
};

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
